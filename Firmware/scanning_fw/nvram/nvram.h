/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __NVRAM_H
#define __NVRAM_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f30x.h"
#include "config.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  uint16_t flash_ok_flag;
  
  // Voltage in volts
  float laser_voltage;
  
  // Voltage in volts
  float apd_voltage;
  
  // Manual setted APD pwm duty value
  uint16_t apd_manual_pwm;
  
  // APD feedback enabled flag
  uint8_t apd_feedback_enabled;
  
  // Comparator threshold voltage, mv
  uint16_t comparator_voltage;
  
  // Coefficient A
  float width_coef_a;
  
  // Coefficient B
  float width_coef_b;
  
  // Zero distance offset, bin. Only for non-rotating mode
  uint16_t zero_offset_bin;
  
  // Reference object distance value, mm
  uint16_t ref_obj_dist_mm;
  
  // Manual setted PWM duty / min safe value
  uint16_t motor_manulal_pwm_duty;
  
  // Motor target speed, rotations per second
  float motor_target_speed;
  
  //Enable auto speed control
  uint8_t motor_feedback_enabled;
  
  // TDC BIN length, mm
  float tdc_bin_length;
  
} nvram_data_t;

extern nvram_data_t nvram_data;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void nvram_use_default_settings(void);
void nvram_save_current_settings(void);
void nvram_read_data(void);
void nvram_prepare_and_save_current_settings(void);

#endif /* __NVRAM_H */
