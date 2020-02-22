// Controlling APD high voltage generation by changing PWM duty
// Measuring APD voltage (ADC + DMA)

/* Includes ------------------------------------------------------------------*/
#include "apd_power.h"
#include "hardware.h"
#include "tdc_driver.h"
#include "main.h"
#include "dist_measurement.h"
#include "nvram.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define APD_ADC_MAX_VALUE       4095

#define APD_ADC_BUFF_SIZE       33//first point is bad

// Delay between pwm decrease steps
#define APD_PWR_DOWN_STEP_MS    200


//Voltage, V
#define APD_PWR_DOWN_THRESHOLD  (2.0f)

typedef enum
{
  APD_FEEDBACK_GO_HIGH = 0,
  APD_FEEDBACK_GO_LOW,
  APD_FEEDBACK_STABLE,
} apd_volt_feedback_t;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
//Current APD voltage, v
float apd_power_voltage = 0.0f;

// Setted APD voltage, V
float apd_power_target_voltage = APD_DEFAULT_VOLTAGE;

// Voltage, captured at "stable" part enter
float apd_power_stable_voltage = 0.0f;

// Enable voltage feedback flag
uint8_t apd_power_feedback_en_flag = 0;

apd_volt_feedback_t apd_volt_feedback_state = APD_FEEDBACK_GO_HIGH;

uint16_t apd_power_pwm_duty_value = APD_DEFAULT_PWM_DUTY;
uint16_t apd_power_pwm_manual_duty_value = APD_DEFAULT_PWM_DUTY;

// Timestamp used for delays
uint32_t apd_power_feedback_timer = 0;

// Buffer for storing ADC data
uint16_t apd_power_adc_raw_data[APD_ADC_BUFF_SIZE];


/* Private function prototypes -----------------------------------------------*/
void apd_power_adc_init(void);
float apd_power_convert_apd_voltage(uint16_t adc_value);
void apd_power_init_dma(void);
void apd_power_start_new_dma_capture(void);
uint16_t apd_power_analyse_adc_dma_data(void);
void apd_power_set_pwm_value(int16_t new_pwm_value);

void apd_power_voltage_feedback_controlling(void);
void apd_power_increase_voltage(void);
void apd_power_decrease_voltage(void);


/* Private functions ---------------------------------------------------------*/
void apd_power_init_all(void)
{
  apd_power_timer_init();
  apd_power_timer_activate_pwm();
  
  apd_power_adc_init();
  apd_power_init_dma();
  
  apd_power_target_voltage = nvram_data.apd_voltage;
  apd_power_pwm_manual_duty_value = nvram_data.apd_manual_pwm;
  apd_power_feedback_en_flag = nvram_data.apd_feedback_enabled;
  
  if (apd_power_feedback_en_flag == 0)
  {
    apd_power_set_pwm_value(apd_power_pwm_manual_duty_value);
  }
}


// Timer is used to for APD boost DC-DC 
void apd_power_timer_init(void)
{
  RCC_APB1PeriphClockCmd(APD_POWER_TIMER_CLK, ENABLE);//Ftimer = SYSCLK
  RCC_AHBPeriphClockCmd(APD_POWER_TIMER_GPIO_CLK, ENABLE);//PWM pin

  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;

  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);

  TIM_DeInit(APD_POWER_TIMER);

  TIM_TimeBaseStructure.TIM_Prescaler = APD_POWER_TIMER_PRESCALER - 1;
  TIM_TimeBaseStructure.TIM_Period = 
      (SystemCoreClock / APD_POWER_TIMER_PRESCALER / APD_POWER_TIMER_FREQ - 1);
  
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(APD_POWER_TIMER, &TIM_TimeBaseStructure);
  TIM_ARRPreloadConfig(APD_POWER_TIMER, ENABLE);
  
  //PWM
  TIM_OCStructInit(&TIM_OCInitStructure);
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = TIM_TimeBaseStructure.TIM_Period / 30;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC2Init(APD_POWER_TIMER, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(APD_POWER_TIMER, TIM_OCPreload_Enable);
  
  //adc
  TIM_OCStructInit(&TIM_OCInitStructure);
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = TIM_TimeBaseStructure.TIM_Period - 10;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC4Init(APD_POWER_TIMER, &TIM_OCInitStructure);
  
  TIM_CtrlPWMOutputs(APD_POWER_TIMER, ENABLE);
  
  // Select the Master Slave Mode
  TIM_SelectMasterSlaveMode(APD_POWER_TIMER, TIM_MasterSlaveMode_Enable);
  // Master Mode selection 
  TIM_SelectOutputTrigger(APD_POWER_TIMER, TIM_TRGOSource_OC4Ref);
  
  TIM_Cmd(APD_POWER_TIMER, ENABLE);
}

//Configure timer pin as PWM out
void apd_power_timer_activate_pwm(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = APD_POWER_TIMER_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(APD_POWER_TIMER_GPIO, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(APD_POWER_TIMER_GPIO, APD_POWER_TIMER_AF_SOURCE, APD_POWER_TIMER_PIN_AFIO);
  
  TIM_CtrlPWMOutputs(APD_POWER_TIMER, ENABLE);
}

//ADC1 & ADC2
void apd_power_adc_init(void)
{
  ADC_InitTypeDef ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_ADCCLKConfig(RCC_ADC12PLLCLK_Div2);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC12, ENABLE);
  
  // Configure ADC Channel 12 pin as analog input
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_InitStructure.GPIO_Pin = APD_FB_ADC_PIN;
  GPIO_Init(APD_FB_ADC_GPIO, &GPIO_InitStructure);

  ADC_DeInit(APD_FB_ADC_NAME);
   
  // Calibration
  ADC_VoltageRegulatorCmd(APD_FB_ADC_NAME, ENABLE);
  dwt_delay_us(1000);
  ADC_SelectCalibrationMode(APD_FB_ADC_NAME, ADC_CalibrationMode_Single);//Single input
  ADC_StartCalibration(APD_FB_ADC_NAME);
  while(ADC_GetCalibrationStatus(APD_FB_ADC_NAME) != RESET);
  
  // ADC Common configuration *************************************************
  ADC_CommonStructInit(&ADC_CommonInitStructure);
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_CommonInitStructure.ADC_Clock = ADC_Clock_SynClkModeDiv1;
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_1;
  ADC_CommonInitStructure.ADC_DMAMode = ADC_DMAMode_OneShot;
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = 0;
  ADC_CommonInit(APD_FB_ADC_NAME, &ADC_CommonInitStructure);

  // ADC2
  ADC_StructInit(&ADC_InitStructure);
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  
  ADC_InitStructure.ADC_ContinuousConvMode = ADC_ContinuousConvMode_Disable;//ext trigger
  ADC_InitStructure.ADC_ExternalTrigConvEvent = ADC_ExternalTrigConvEvent_15;//TIM3_CC4
  ADC_InitStructure.ADC_ExternalTrigEventEdge = ADC_ExternalTrigEventEdge_RisingEdge;
    
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_OverrunMode = ADC_OverrunMode_Enable;//Important ??
  ADC_InitStructure.ADC_AutoInjMode = ADC_AutoInjec_Disable;
  ADC_InitStructure.ADC_NbrOfRegChannel = 1;// One channel for this ADC
  ADC_Init(APD_FB_ADC_NAME, &ADC_InitStructure);

  ADC_RegularChannelConfig(APD_FB_ADC_NAME, APD_FB_ADC_CHANNEL, 1, ADC_SAMPLING_TIME);

  ADC_DMAConfig(APD_FB_ADC_NAME, ADC_DMAMode_OneShot);
  ADC_DMACmd(APD_FB_ADC_NAME, ENABLE);

  ADC_Cmd(APD_FB_ADC_NAME, ENABLE);

  while(!ADC_GetFlagStatus(APD_FB_ADC_NAME, ADC_FLAG_RDY));

  ADC_StartConversion(APD_FB_ADC_NAME);
}

// DMA is used to capture data from ADC
void apd_power_init_dma(void)
{
  DMA_InitTypeDef DMA_InitStructure;
  RCC_AHBPeriphClockCmd(APD_FB_DMA_CLK, ENABLE);
  
  DMA_DeInit(APD_FB_DMA_CHANNEL);//master
  DMA_StructInit(&DMA_InitStructure);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&APD_FB_ADC_NAME->DR;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&apd_power_adc_raw_data[0];
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = APD_ADC_BUFF_SIZE;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(APD_FB_DMA_CHANNEL, &DMA_InitStructure);
  
  DMA_Cmd(APD_FB_DMA_CHANNEL, ENABLE);
}

void apd_power_start_new_dma_capture(void)
{
  DMA_Cmd(APD_FB_DMA_CHANNEL, DISABLE);
  APD_FB_DMA_CHANNEL->CNDTR = APD_ADC_BUFF_SIZE;
  APD_FB_DMA_CHANNEL->CMAR = (uint32_t)&apd_power_adc_raw_data[0];
  DMA_ClearFlag(APD_FB_DMA_DONE_FLAG);
  
  ADC_Cmd(APD_FB_ADC_NAME, DISABLE);
  ADC_ClearFlag(APD_FB_ADC_NAME, ADC_FLAG_OVR);
  DMA_Cmd(APD_FB_DMA_CHANNEL, ENABLE);
  ADC_Cmd(APD_FB_ADC_NAME, ENABLE);  
  ADC_StartConversion(APD_FB_ADC_NAME);
}

// Periodically called from Main()
// 10 ms period
void apd_power_voltage_controlling(void)
{
  //uint16_t raw_adc = APD_FB_ADC_NAME->DR;
  uint16_t raw_adc = apd_power_analyse_adc_dma_data();
  float adc_voltage = apd_power_convert_apd_voltage(raw_adc);
  apd_power_voltage = adc_voltage;
  
  if (DMA_GetFlagStatus(APD_FB_DMA_DONE_FLAG) == SET)
  {
    apd_power_start_new_dma_capture();
  }
  
  if (apd_power_feedback_en_flag)
    apd_power_voltage_feedback_controlling();
  
}

// Called when APD voltage feedback is enabled
void apd_power_voltage_feedback_controlling(void)
{
  if (apd_volt_feedback_state == APD_FEEDBACK_GO_HIGH)
  {
    if (apd_power_voltage < apd_power_target_voltage)
    {
      apd_power_increase_voltage();
    }
    else
    {
      apd_volt_feedback_state = APD_FEEDBACK_GO_LOW;
    }
  }
  else if (apd_volt_feedback_state == APD_FEEDBACK_GO_LOW)
  {
    if (TIMER_ELAPSED(apd_power_feedback_timer))
    {
      START_TIMER(apd_power_feedback_timer, APD_PWR_DOWN_STEP_MS);
      if (apd_power_voltage > apd_power_target_voltage)
      {
        apd_power_decrease_voltage();
      }
      else
      {
        apd_power_stable_voltage = apd_power_voltage;
        apd_volt_feedback_state = APD_FEEDBACK_STABLE;
      }
    }
  }
  else if (apd_volt_feedback_state == APD_FEEDBACK_STABLE)
  {
    if (apd_power_voltage < (apd_power_stable_voltage - APD_PWR_DOWN_THRESHOLD))
    {
      // voltage dropped
      apd_volt_feedback_state = APD_FEEDBACK_GO_HIGH;
    }
    else if (apd_power_voltage > apd_power_target_voltage)
    {
      //voltage increased
      apd_volt_feedback_state = APD_FEEDBACK_GO_LOW;
    }
  }
}

// Increase PWM value for one step
void apd_power_increase_voltage(void)
{
  if (apd_power_pwm_duty_value > APD_PWR_MAX_PWM_VALUE) //protection
    return;
  
  apd_power_pwm_duty_value++;
  apd_power_set_pwm_value(apd_power_pwm_duty_value);
}

// Decrease PWM value for one step
void apd_power_decrease_voltage(void)
{
  if (apd_power_pwm_duty_value < 10) //protection
    return;
  
  apd_power_pwm_duty_value--;
  apd_power_set_pwm_value(apd_power_pwm_duty_value);
}

// Calculate average value from DMA results
// Return average value in raw ADC points
uint16_t apd_power_analyse_adc_dma_data(void)
{
  uint32_t summ = 0;
  //skip first point, it is bad
  for (uint8_t i = 1; i < APD_ADC_BUFF_SIZE; i++)
  {
    summ+= apd_power_adc_raw_data[i];
  }
  
  return (summ / (APD_ADC_BUFF_SIZE - 1));
}

// Convert raw ADC value to voltage in volts
float apd_power_convert_apd_voltage(uint16_t adc_value)
{
  float adc_voltage_v = (float)adc_value * MCU_VREF / (float)APD_ADC_MAX_VALUE;
  return (adc_voltage_v * (APD_FB_ADC_UPPER_R / APD_FB_ADC_LOWER_R + 1.0f));
}

// Set new PWM timer duty period
void apd_power_set_pwm_value(int16_t new_pwm_value)
{
  if (new_pwm_value < APD_POWER_TIMER->ARR)
  {
    APD_POWER_TIMER->APD_POWER_TIMER_PWM_REG = new_pwm_value;
    apd_power_pwm_duty_value = new_pwm_value;
  }
}

// Parse mavlink command
void apd_power_parse_new_setings(mavlink_set_apd_voltage_t msg)
{
  if (msg.pwm_value >= 0)//manual mode
  {
      apd_power_set_pwm_value(msg.pwm_value);
      apd_power_feedback_en_flag = 0;
      apd_power_pwm_manual_duty_value = msg.pwm_value;
  }
  else
  {
    if (msg.voltage > 0.0f)
    {
      apd_power_target_voltage = msg.voltage;
      apd_power_stable_voltage = apd_power_target_voltage;
      apd_volt_feedback_state = APD_FEEDBACK_STABLE;
      apd_power_feedback_en_flag = 1;
    }
  }
}

