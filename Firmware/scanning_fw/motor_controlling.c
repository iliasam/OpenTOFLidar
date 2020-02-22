// Controlling mirror speed by changing PWM duty
// BLDC Motor controller is DRV11873

/* Includes ------------------------------------------------------------------*/
#include "motor_controlling.h"
#include "encoder_processing.h"
#include "hardware.h"
#include "nvram.h"
#include "main.h"
#include "math.h"

/* Private typedef -----------------------------------------------------------*/
#define MOTOR_FAIL_MASK         (ENCODER_SYNC_FAIL_FLAG | MIRROR_STOPPED_FLAG)

typedef enum
{
  // Waiting for motor speed stabilization
  MOTOR_STARTUP_WAIT = 0,
  MOTOR_FEEDBACK_RUN,
} motor_ctrl_state_t;

/* Private define ------------------------------------------------------------*/
#define US_IN_SEC               (1000000.0f)

//Delay in ms after start. Motor should be working, waiting for encoder data
#define MOTOR_START_DELAY       (1000)

// Size of buffer for analysing speed stability
#define MOTOR_SPEED_BUFER_SIZE  (10)

// Speed is stable if difference smaller than this value, RPS
#define MOTOR_SPEED_THRESHOLD   (1.0f)


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
// Current motor speed - rotations per second (RPS)
float motor_ctrl_current_speed = 0.0f;

uint16_t motor_ctrl_manual_pwm_duty = MOTOR_DEFAULT_PWM_DUTY;
uint16_t motor_ctrl_current_pwm_duty = MOTOR_DEFAULT_PWM_DUTY;

// Automated speed feedback using encoder data
uint8_t motor_ctrl_auto_speed_enabled = 0;

motor_ctrl_state_t motor_ctrl_state = MOTOR_STARTUP_WAIT;

volatile float motor_ctrl_i_coeff = MOTOR_CONTROLLING_I_COEF;
float motor_ctrl_i_part = 0.0f;
float motor_ctrl_target_speed = MOTOR_DEFAULT_SPEED;

extern uint32_t encoder_proc_rotation_period_us;
extern uint16_t device_state_mask;

/* Private function prototypes -----------------------------------------------*/
void motor_ctrl_timer_init(void);
void motor_ctrl_set_pwm_value(uint16_t new_duty);
void motor_ctrl_speed_controlling(void);
uint8_t motor_ctrl_is_speed_stable(void);

/* Private functions ---------------------------------------------------------*/

void motor_ctrl_init(void)
{
  motor_ctrl_timer_init();
  
  motor_ctrl_auto_speed_enabled = nvram_data.motor_feedback_enabled;
  if (nvram_data.motor_target_speed < MOTOR_MAX_SPEED)
    motor_ctrl_target_speed = nvram_data.motor_target_speed;
  //starting in manual mode
  motor_ctrl_manual_pwm_duty = nvram_data.motor_manulal_pwm_duty;
  motor_ctrl_set_pwm_value(motor_ctrl_manual_pwm_duty);
}

// Motor controlling handling
// Called every 100ms
void motor_ctrl_handling(void)
{
  motor_ctrl_current_speed = US_IN_SEC / encoder_proc_rotation_period_us;
  
  if ((motor_ctrl_current_speed > MOTOR_MAX_SPEED) || 
      (motor_ctrl_current_speed < MOTOR_MIN_SPEED))
    device_state_mask |= MIRROR_WRONG_SPEED;
  else
    device_state_mask &= ~MIRROR_WRONG_SPEED;

  if (motor_ctrl_auto_speed_enabled)
    motor_ctrl_speed_controlling();
}

void motor_ctrl_speed_controlling(void)
{
  // Wait for encoder (if motor is running at startup)
  if (ms_tick < MOTOR_START_DELAY)
    return;
  
  if (motor_ctrl_state == MOTOR_STARTUP_WAIT)
  {
    if (motor_ctrl_is_speed_stable())
    {
      motor_ctrl_state = MOTOR_FEEDBACK_RUN;
    }
  }
  else if (motor_ctrl_state == MOTOR_FEEDBACK_RUN)
  {
    if ((device_state_mask & MOTOR_FAIL_MASK) != 0)
    {
      //This duty is safe
      motor_ctrl_set_pwm_value(motor_ctrl_manual_pwm_duty);
      // Stop auto controlling
      motor_ctrl_state = MOTOR_STARTUP_WAIT;
      return;
    }
    
    //positive error -> need to increase speed
    float error = motor_ctrl_target_speed - motor_ctrl_current_speed;
    motor_ctrl_i_part += error * motor_ctrl_i_coeff;
    if (motor_ctrl_i_part < 0.0f)
      motor_ctrl_i_part = 0.0f;
    float result = (float)motor_ctrl_manual_pwm_duty + motor_ctrl_i_part;
    motor_ctrl_set_pwm_value((int16_t)result);
  }
}

// Return 1 is motor speed is stable
uint8_t motor_ctrl_is_speed_stable(void)
{
  static float motor_speed_buf[MOTOR_SPEED_BUFER_SIZE];
  static uint8_t pos = 0;
  float avr_speed = 0.0f;
  
  pos++;
  if (pos >= MOTOR_SPEED_BUFER_SIZE)
    pos = 0;
  motor_speed_buf[pos] = motor_ctrl_current_speed;
  
  for (uint8_t i = 0; i < MOTOR_SPEED_BUFER_SIZE; i++)
  {
    avr_speed += motor_speed_buf[i];
  }
  avr_speed = avr_speed / MOTOR_SPEED_BUFER_SIZE;
  
  for (uint8_t i = 0; i < MOTOR_SPEED_BUFER_SIZE; i++)
  {
    if (fabs(avr_speed - motor_speed_buf[i]) > MOTOR_SPEED_THRESHOLD)
      return 0;//to big difference
  }
  return 1;
}

void motor_ctrl_timer_init(void)
{
  RCC_APB1PeriphClockCmd(MOTOR_TIMER_CLK, ENABLE);//Ftimer = SYSCLK
  RCC_AHBPeriphClockCmd(MOTOR_TIMER_GPIO_CLK, ENABLE);//PWM pin

  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = MOTOR_TIMER_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(MOTOR_TIMER_GPIO, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(MOTOR_TIMER_GPIO, MOTOR_TIMER_AF_SOURCE, MOTOR_TIMER_PIN_AFIO);

  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);

  TIM_DeInit(MOTOR_TIMER);

  TIM_TimeBaseStructure.TIM_Prescaler = MOTOR_TIMER_PRESCALER - 1;
  TIM_TimeBaseStructure.TIM_Period = 
      (SystemCoreClock / MOTOR_TIMER_PRESCALER / MOTOR_TIMER_FREQ - 1);
  
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(MOTOR_TIMER, &TIM_TimeBaseStructure);
  TIM_ARRPreloadConfig(MOTOR_TIMER, ENABLE);
  
  //PWM
  TIM_OCStructInit(&TIM_OCInitStructure);
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = motor_ctrl_manual_pwm_duty;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  
  #if (MOTOR_TIMER_CHANNEL == 2)
  TIM_OC2Init(MOTOR_TIMER, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(MOTOR_TIMER, TIM_OCPreload_Enable);
  #elif (MOTOR_TIMER_CHANNEL == 3)
  TIM_OC3Init(MOTOR_TIMER, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(MOTOR_TIMER, TIM_OCPreload_Enable);
  #else
  #error "Channel not defined!"
  #endif

  TIM_CtrlPWMOutputs(MOTOR_TIMER, ENABLE);

  TIM_Cmd(MOTOR_TIMER, ENABLE);
}

// Set new PWM timer duty period
void motor_ctrl_set_pwm_value(uint16_t new_duty)
{
  if (new_duty < MOTOR_TIMER->ARR)
  {
    MOTOR_TIMER->MOTOR_TIMER_PWM_REG = new_duty;
    motor_ctrl_current_pwm_duty = new_duty;
  }
}

void motor_ctrl_manual_set_pwm_duty(uint16_t duty)
{
  motor_ctrl_manual_pwm_duty = duty;
  motor_ctrl_set_pwm_value(duty);
  motor_ctrl_auto_speed_enabled = 0;
}

// Speed in RPS
void motor_ctrl_set_auto_speed(float speed)
{
  if (speed > MOTOR_MAX_SPEED)
    return;
  
  motor_ctrl_target_speed = speed;
  motor_ctrl_auto_speed_enabled = 1;
}