

/* Includes ------------------------------------------------------------------*/
#include "encoder_processing.h"
#include "capture_controlling.h"
#include "dist_measurement.h"
#include "mavlink_handling.h"
#include "hardware.h"
#include "nvram.h"
#include "math.h"
#include "main.h"
#include "tdc_driver.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

// Number of captured points
#define CAPT_POINTS_CNT         (uint16_t)(360.0f / CAPTURE_ANG_RESOL)

// Encoder angular step, deg
// ~5.5 deg per event (65 holes encoder)
#define ENCODER_ANG_STEP        (360.0f / (float)ENCODER_HOLES_CNT)

// Number of dist measurements that should be done during one encoder period
#define CAPT_MEAS_PER_ENCODER_PERIOD    ((float)CAPT_POINTS_CNT / (float)ENCODER_HOLES_CNT)


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

// Current mirror angle in degrees
float capture_ctr_current_angle = 0.0f;

//Buffer for storing RAW TDC values
tdc_point_t scan_raw_buffer0[CAPT_POINTS_CNT];
tdc_point_t scan_raw_buffer1[CAPT_POINTS_CNT];

tdc_point_t *capture_ctr_write_ptr = scan_raw_buffer0;
tdc_point_t *capture_ctr_read_ptr  = scan_raw_buffer1;

// New raw data is ready for processing
// This flag is set at zero crossing, and cleared after data processing
uint16_t scan_dist_raw_data_ready_flag = 0;

//Buffer for storing processed data - distances in mm
uint16_t scan_dist_buffer0[CAPT_POINTS_CNT];
uint16_t scan_dist_buffer1[CAPT_POINTS_CNT];

uint16_t *capture_ctr_dist_write_ptr = scan_dist_buffer0;
uint16_t *capture_ctr_dist_read_ptr  = scan_dist_buffer1;


uint8_t dist_measurenent_enabled = 0;

extern uint16_t device_state_mask;

/* Private function prototypes -----------------------------------------------*/
void capture_ctr_init_capture_timer(void);
void capture_ctr_refresh_timer(uint16_t new_period);
void capture_ctr_make_measurement(float angle);
void capture_ctr_switch_buffers(void);
void capture_ctr_reset_timer(void);
void capture_ctr_switch_dist_buffers(void);

/* Private functions ---------------------------------------------------------*/

// Capture controlling init
void capture_ctr_init(void)
{
  capture_ctr_init_capture_timer();
  
  //values for testing
  for (uint16_t i = 0; i < CAPT_POINTS_CNT; i++)
  {
    scan_dist_buffer0[i] = 800;
    scan_dist_buffer1[i] = 2500;
  }
}

// Must be called periodically
void capture_ctr_data_processing(void)
{
  if (device_state_mask & LASER_DISABLE_MASK)
    dist_measurenent_enabled = 0;
  else
    dist_measurenent_enabled = 1;
  
  // "scan_dist_raw_data_ready_flag" is set after zero crossing
  // we hope that scan data are already send
  if (scan_dist_raw_data_ready_flag && dist_measurenent_enabled)
  {
    //TEST_GPIO->ODR |= TEST_PIN;
    // First values could be wrong
    dist_measurement_update_ref_value(capture_ctr_read_ptr[2]);
    
    // Can take a lot of time
    for (uint16_t i = 0; i < CAPT_POINTS_CNT; i++)
    {
      capture_ctr_dist_write_ptr[i] = 
        dist_measurement_process_data(
          capture_ctr_read_ptr[i].start_value, 
          capture_ctr_read_ptr[i].width_value);
    }
    //TEST_GPIO->ODR &= ~TEST_PIN;
    capture_ctr_switch_dist_buffers();
    mavlink_send_scan_data(capture_ctr_dist_read_ptr, CAPT_POINTS_CNT);
    
    scan_dist_raw_data_ready_flag = 0;
  }
}

// Capture timer interrupt
void CAPTURE_TIMER_IRQ_HANDLER(void)
{
  TEST_GPIO->ODR |= TEST_PIN;
  if (TIM_GetITStatus(CAPTURE_TIMER, CAPTURE_TIMER_IT_FLAG) != RESET)
  {
    TIM_ClearITPendingBit(CAPTURE_TIMER, CAPTURE_TIMER_IT_FLAG);
    
    capture_ctr_current_angle += CAPTURE_ANG_RESOL;
    if (dist_measurenent_enabled == 1)
      capture_ctr_make_measurement(capture_ctr_current_angle);//take a lot of time
    
    TEST_GPIO->ODR &= ~TEST_PIN;
  }
}

void capture_ctr_make_measurement(float angle)
{
  // Used during encoder "zero" hole time
  if (angle > 360.0)
    angle = angle - 360.0f;
  
  uint16_t pos = (uint16_t)roundf(angle / CAPTURE_ANG_RESOL);
  // Read previous measurement
  //capture_ctr_write_ptr[pos] = tdc_read_two_registers();
  capture_ctr_write_ptr[pos] = tdc_read_three_registers();
  tdc_start_pulse();
}

// Called from encoder interrupt
// "last_period" is time from prev encoder event in encoder_timer ticks
void capture_ctr_encoder_event(uint16_t event_cnt, uint16_t last_period)
{
  //TEST_GPIO->ODR^= TEST_PIN;
  capture_ctr_current_angle = (float)event_cnt * ENCODER_ANG_STEP;
  uint16_t capture_timer_period = 
    (uint16_t)((float)last_period / CAPT_MEAS_PER_ENCODER_PERIOD);
  capture_ctr_refresh_timer(capture_timer_period);
}

// Called from encoder interrupt
void capture_ctr_encoder_zero_event(void)
{
  // Zero hole is closed, we don't see real zero
  capture_ctr_current_angle = ENCODER_ANG_STEP;
  capture_ctr_switch_buffers();
  scan_dist_raw_data_ready_flag = 1;
  capture_ctr_reset_timer();
}

void capture_ctr_switch_buffers(void)
{
  if (capture_ctr_write_ptr == scan_raw_buffer0)
  {
    capture_ctr_write_ptr = scan_raw_buffer1;
    capture_ctr_read_ptr  = scan_raw_buffer0;
  }
  else
  {
    capture_ctr_write_ptr = scan_raw_buffer0;
    capture_ctr_read_ptr  = scan_raw_buffer1;
  }
  // Buffers have the same size
  memset(capture_ctr_write_ptr, 0, sizeof(scan_raw_buffer0));
}

void capture_ctr_switch_dist_buffers(void)
{
  if (capture_ctr_dist_write_ptr == scan_dist_buffer0)
  {
    capture_ctr_dist_write_ptr = scan_dist_buffer1;
    capture_ctr_dist_read_ptr  = scan_dist_buffer0;
  }
  else
  {
    capture_ctr_dist_write_ptr = scan_dist_buffer0;
    capture_ctr_dist_read_ptr  = scan_dist_buffer1;
  }
}

void capture_ctr_init_capture_timer(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  
  RCC_APB2PeriphClockCmd(CAPTURE_TIMER_CLK, ENABLE);
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  
  TIM_TimeBaseStructure.TIM_Prescaler = CAPTURE_TIMER_PRESCALER;
  TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(CAPTURE_TIMER, &TIM_TimeBaseStructure);
  TIM_ARRPreloadConfig(CAPTURE_TIMER, ENABLE);
  
  TIM_ClearITPendingBit(CAPTURE_TIMER, CAPTURE_TIMER_IT_FLAG);
  TIM_ITConfig(CAPTURE_TIMER, CAPTURE_TIMER_IT_FLAG, ENABLE);
  
  NVIC_InitStructure.NVIC_IRQChannel = CAPTURE_TIMER_IRQ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 
    CAPTURE_TIMER_IRQ_PRIORITY;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  TIM_Cmd(CAPTURE_TIMER, ENABLE);
}

// Reset and set new period for capture timer
void capture_ctr_refresh_timer(uint16_t new_period)
{
  CAPTURE_TIMER->CR1&= ~TIM_CR1_CEN;//disable timer
  TIM_SetCounter(CAPTURE_TIMER, 0);
  TIM_SetAutoreload(CAPTURE_TIMER, new_period - 1);
  CAPTURE_TIMER->EGR|= TIM_EGR_UG;//update all registers and prescaler
  CAPTURE_TIMER->CR1|= TIM_CR1_CEN;//enable timer
}

void capture_ctr_reset_timer(void)
{
  CAPTURE_TIMER->CR1&= ~TIM_CR1_CEN;//disable timer
  TIM_SetCounter(CAPTURE_TIMER, 0);
  CAPTURE_TIMER->EGR|= TIM_EGR_UG;//update all registers and prescaler
  CAPTURE_TIMER->CR1|= TIM_CR1_CEN;//enable timer
}