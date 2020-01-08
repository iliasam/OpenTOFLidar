/* Includes ------------------------------------------------------------------*/
#include "hardware.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void hardware_init_rcc(void);
void hardware_init_led(void);

void hardware_dwt_init(void);
uint32_t hardware_dwt_get(void);
uint8_t hardware_dwt_comapre(int32_t tp);
void hardware_init_dac(void);
void hardware_enable_tdc_clock(void);
void hardware_init_motor_line(void);

/* Private functions ---------------------------------------------------------*/

void hardware_init_all(void)
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  
  hardware_init_rcc();
  
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq (&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);
  
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
  
  hardware_dwt_init();
  hardware_init_led();
  hardware_init_dac();
  hardware_init_motor_line();
  hardware_enable_tdc_clock();
}

void hardware_init_led(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = LED_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(LED_GPIO, &GPIO_InitStructure);
  
  GPIO_ResetBits(LED_GPIO, LED_PIN);
}

//Initialize main clock system
void hardware_init_rcc(void)
{
  FLASH_SetLatency(FLASH_Latency_2);
  FLASH_PrefetchBufferCmd(ENABLE);
    
  //switch to HSI
  RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
  while (RCC_GetSYSCLKSource() != 0x00) {}
  RCC_DeInit();
  
  //enable HSE
  RCC_HSEConfig(RCC_HSE_ON);
  RCC_WaitForHSEStartUp();
  while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET) {}
  RCC_PLLConfig(RCC_PLLSource_PREDIV1,RCC_PLLMul_9); // PLL config 8*9=72
  RCC_PLLCmd(ENABLE);
  while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) {}
  //switch to HSE
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
  while (RCC_GetSYSCLKSource() != 0x08) {}
}

//Init DWT counter
void hardware_dwt_init(void)
{
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  DWT->CYCCNT = 0;
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

void hardware_init_dac(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  DAC_InitTypeDef DAC_InitStructure;
  
  DAC_DeInit(DAC_NAME);
  
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_Pin = LASER_DAC_PIN | APD_COMP_DAC_PIN;
  GPIO_Init(DAC_GPIO, &GPIO_InitStructure);
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
  DAC_StructInit(&DAC_InitStructure);
  DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
  DAC_InitStructure.DAC_Buffer_Switch = DAC_BufferSwitch_Disable;
  DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
  DAC_Init(DAC_NAME, LASER_DAC_CHANNEL, &DAC_InitStructure);
  DAC_Init(DAC_NAME, APD_COMP_DAC_CHANNEL, &DAC_InitStructure);
  
  DAC_Cmd(DAC_NAME, LASER_DAC_CHANNEL, ENABLE);
  DAC_Cmd(DAC_NAME, APD_COMP_DAC_CHANNEL, ENABLE);

  hardware_set_laser_voltage(10.0);
}

// Disable motor pwm
void hardware_init_motor_line(void)
{
  RCC_AHBPeriphClockCmd(MOTOR_TIMER_GPIO_CLK, ENABLE);//PWM pin
  GPIO_InitTypeDef GPIO_InitStructure;
  
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = MOTOR_TIMER_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(MOTOR_TIMER_GPIO, &GPIO_InitStructure);
  
  GPIO_ResetBits(MOTOR_TIMER_GPIO, MOTOR_TIMER_PIN);
}


//voltage - in volts
void hardware_set_laser_voltage(float voltage)
{
  if (voltage > 18.0f)
    voltage = 18.0f;
  
  if (voltage < 7.0f)
    voltage = 7.0f;
  
  float tmp1 = LASER_DCDC_VREF * (1 + (LASER_DCDC_R_UP / LASER_DCDC_R_DOWN));
  
  float dac_voltage = 0.0f;
  dac_voltage = LASER_DCDC_VREF - (voltage - tmp1) * (LASER_DCDC_R_DAC / LASER_DCDC_R_UP);
  
  float dac_value = dac_voltage * DAC_MAXIUM / MCU_VREF;
  DAC_SetChannel2Data(DAC_NAME, DAC_Align_12b_R, (uint16_t)dac_value);
}

// Set APD comparator threshold voltage
// comp_threshold - in millivolts
void hardware_set_apd_comp_voltage(uint16_t comp_threshold)
{
  //dac voltage in volts
  float dac_voltage = (float)comp_threshold * 0.001f * APD_COMP_R_COMMON / APD_COMP_R_MAIN;
  
  float dac_value = dac_voltage * DAC_MAXIUM / MCU_VREF;
  if (dac_value > DAC_MAXIUM)
    dac_value = DAC_MAXIUM;
  
  DAC_SetChannel1Data(DAC_NAME, DAC_Align_12b_R, (uint16_t)dac_value);
}

void hardware_enable_tdc_clock(void)
{
  RCC_APB1PeriphClockCmd(APD_POWER_TIMER_CLK, ENABLE);//Ftimer = SYSCLK
    
  GPIO_InitTypeDef GPIO_InitStructure;
  
  //PA8 should be configured in alternate function mode.
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  // Alternate function source set 
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_0); 
  
  RCC_MCOConfig(RCC_MCOSource_HSE);
}


// ***************************************************************************

uint32_t hardware_dwt_get(void)
{
  return DWT->CYCCNT;
}

inline uint8_t hardware_dwt_comapre(int32_t tp)
{
  return (((int32_t)hardware_dwt_get() - tp) < 0);
}

// Delay for "us"
void dwt_delay_us(uint32_t us)
{
  int32_t tp = hardware_dwt_get() + us * (SystemCoreClock / 1000000);
  while (hardware_dwt_comapre(tp));
}

// Delay for "ms"
void dwt_delay_ms(uint32_t ms)
{
  dwt_delay_us(ms * 1000);
}


