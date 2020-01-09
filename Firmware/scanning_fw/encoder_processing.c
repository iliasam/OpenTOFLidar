// Encoder is connected to MCU comparator
// Comparator output is connected to "ENCODER_COMP_TIMER" Capture input
// Compare interrupt is generated at every comparator event

/* Includes ------------------------------------------------------------------*/
#include "encoder_processing.h"
#include "capture_controlling.h"
#include "hardware.h"
#include "nvram.h"
#include "main.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
// Delay after encoder event meaning that mirror is stopped
#define ENCODER_TIMEOUT_MS      (5)


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
// Capture timer values
uint16_t encoder_proc_capture_old = 0;
// Captured value of timer - encoder event
uint16_t encoder_proc_capture_now = 0;

// Mirror rotation period, in us
uint32_t encoder_proc_rotation_period_us  = 0;

// Previous time of zero crossing, DWT ticks
uint32_t encoder_proc_zero_prev_timestamp = 0;

// Previous encoder event time, ms
uint32_t encoder_proc_event_timestamp_ms = 0;

// Time between encoder events, in timer ticks
volatile uint16_t enc_period;

//Number of encoder events from zero detection
volatile uint16_t encoder_proc_event_cnt  = 0; 

extern uint16_t device_state_mask;

/* Private function prototypes -----------------------------------------------*/
void encoder_proc_init_comparator(void);
void encoder_proc_init_encoder_timer(void);
uint8_t encoder_proc_check_zero_cross(uint16_t time);
void encoder_proc_zero_crossing(void);

/* Private functions ---------------------------------------------------------*/

void encoder_proc_init(void)
{
  encoder_proc_init_comparator();
  encoder_proc_init_encoder_timer();
}

// Interrupt from timer (connected to encoder comparator)
void ENCODER_COMP_TIMER_IRQ_HANDLER(void)
{
  if (TIM_GetITStatus(ENCODER_COMP_TIMER, ENCODER_COMP_TIMER_IT_FLAG) != RESET)
  {
    TIM_ClearITPendingBit(ENCODER_COMP_TIMER, ENCODER_COMP_TIMER_IT_FLAG);
    encoder_proc_capture_old = encoder_proc_capture_now;
    encoder_proc_capture_now = ENCODER_COMP_GET_CAPTURD_VALUE(ENCODER_COMP_TIMER);
    
    if (encoder_proc_capture_now >= encoder_proc_capture_old) 
      enc_period = encoder_proc_capture_now - encoder_proc_capture_old;
    else 
      enc_period = 0xFFFF - encoder_proc_capture_old + encoder_proc_capture_now;
    
    encoder_proc_event_cnt++;
    encoder_proc_event_timestamp_ms = ms_tick;
    
    if (encoder_proc_check_zero_cross(enc_period) != 0)
    {
      //Zero cross detected
      encoder_proc_zero_crossing();
      //dist_measurement_process_current_data();
      capture_ctr_encoder_zero_event();
    }
    else
    {
      capture_ctr_encoder_event(encoder_proc_event_cnt, enc_period);
    }
  }// end of interrupt check
}

// Process zero crossing event
// Called from timer interrupt
void encoder_proc_zero_crossing(void)
{
  // Check number of holes detected
  if (encoder_proc_event_cnt != ENCODER_HOLES_CNT)
  {
    device_state_mask |= ENCODER_SYNC_FAIL_FLAG;
  }
  else
  {
    device_state_mask &= ~ENCODER_SYNC_FAIL_FLAG;
  }
  
  encoder_proc_event_cnt = 1; //Real zero hole is not visible
  encoder_proc_rotation_period_us = 
    (hardware_dwt_get() - encoder_proc_zero_prev_timestamp) / 
    (SystemCoreClock / 1000000);
  encoder_proc_zero_prev_timestamp = hardware_dwt_get();
}

// Called periodically - every 10 ms
void encoder_proc_perodic_handling(void)
{
  if ((ms_tick - encoder_proc_event_timestamp_ms) > ENCODER_TIMEOUT_MS)
  {
    device_state_mask |= MIRROR_STOPPED_FLAG;
  }
  else
  {
    device_state_mask &= ~MIRROR_STOPPED_FLAG;
  }
}

// Init encoder comparator
void encoder_proc_init_comparator(void)
{
  COMP_InitTypeDef COMP_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_AHBPeriphClockCmd(ENCODER_COMP_GPIO_CLK, ENABLE);
  
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = ENCODER_COMP_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(ENCODER_COMP_GPIO, &GPIO_InitStructure);
  
  /* COMP Peripheral clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  COMP_StructInit(&COMP_InitStructure);
  
  COMP_InitStructure.COMP_NonInvertingInput = ENCODER_COMP_POS_SRC;
  COMP_InitStructure.COMP_InvertingInput = ENCODER_COMP_NEG_SRC;
  COMP_InitStructure.COMP_Output = ENCODER_COMP_OUTPUT;
  COMP_InitStructure.COMP_Mode = COMP_Mode_MediumSpeed;
  COMP_InitStructure.COMP_Hysteresis = COMP_Hysteresis_Medium;
  COMP_Init(ENCODER_COMP, &COMP_InitStructure);
  
  COMP_Cmd(ENCODER_COMP, ENABLE);
}

// Init timer used for processing events from encoder comparator 
void encoder_proc_init_encoder_timer(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  
  RCC_APB2PeriphClockCmd(ENCODER_COMP_TIMER_CLK, ENABLE);
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  
  TIM_TimeBaseStructure.TIM_Prescaler = ENCODER_COMP_TIMER_PRESCALER;
  TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(ENCODER_COMP_TIMER, &TIM_TimeBaseStructure);
  
  // channel1 - input capture
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_Channel = ENCODER_COMP_TIMER_CH;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 12;//uart produce some noise
  TIM_ICInit(ENCODER_COMP_TIMER, &TIM_ICInitStructure);
  
  TIM_ARRPreloadConfig(ENCODER_COMP_TIMER, ENABLE);
  
  TIM_ClearITPendingBit(ENCODER_COMP_TIMER, ENCODER_COMP_TIMER_IT_FLAG);
  TIM_ITConfig(ENCODER_COMP_TIMER, ENCODER_COMP_TIMER_IT_FLAG, ENABLE);
  
  NVIC_InitStructure.NVIC_IRQChannel = ENCODER_COMP_TIMER_IRQ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 
    ENCODER_COMP_TIMER_IRQ_PRIORITY;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  TIM_Cmd(ENCODER_COMP_TIMER, ENABLE);
}

// Calculating average period
// If "time" 1.5 times bigger than average value, return 1
uint8_t encoder_proc_check_zero_cross(uint16_t time)
{
  static uint16_t times[4];
  static uint8_t pos = 0;//pos = 0-3
  uint16_t avr_time = 0;//average period
  uint16_t result;

  times[pos] = time;
  pos++;
  pos &= 3;
  avr_time = (times[0] + times[1] + times[2] + times[3]) / 4;
  time = time * 4;
  result = time / avr_time;
  if (result >= 5) 
    return 1;
  else 
    return 0;//6/4 = 1.5
}