/* Includes ------------------------------------------------------------------*/
#include "stm32f3_flash.h"
#include "nvram.h"
#include "main.h"
#include "string.h"
#include "apd_power.h"

/* Private typedef -----------------------------------------------------------*/
#define NVRAM_FLASH_OK_MASK     0xABCD

/* Private define ------------------------------------------------------------*/
//Number of the sector for storing data
#define NVRAM_FLASH_SECTOR      (((128 * FLASH_BYTES_PER_KB) / FLASH_SECTOR_SIZE) - 2)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
nvram_data_t nvram_data;

extern float apd_power_target_voltage;
extern float current_laser_volt;
extern uint16_t apd_comp_threshold_mv;
extern uint8_t apd_power_feedback_en_flag;
extern uint16_t apd_power_pwm_manual_duty_value;
extern float dist_meas_width_coef_a;
extern float dist_meas_width_coef_b;
extern uint16_t dist_meas_zero_offset_bin;
extern uint16_t dist_meas_ref_dist_mm;
extern uint8_t motor_ctrl_auto_speed_enabled;
extern float motor_ctrl_target_speed;
extern uint16_t motor_ctrl_manual_pwm_duty;
extern float dist_meas_bin_length;

/* Private function prototypes -----------------------------------------------*/


/* Private functions ---------------------------------------------------------*/

void nvram_use_default_settings(void)
{
  nvram_data.apd_voltage = APD_DEFAULT_VOLTAGE;
  nvram_data.apd_manual_pwm = APD_DEFAULT_PWM_DUTY;
  nvram_data.apd_feedback_enabled = 0;//manual mode
  nvram_data.laser_voltage = LASER_DEFAULT_VOLTAGE;
  nvram_data.comparator_voltage = APD_COMP_DEFAULT_VOLT_MV;
  nvram_data.width_coef_a = 0.0f;
  nvram_data.width_coef_b = 0.0f;
  nvram_data.zero_offset_bin = 0;
  nvram_data.ref_obj_dist_mm = 0;
  nvram_data.tdc_bin_length = DEFAULT_DIST_BIN_LENGTH;
  
  nvram_data.motor_feedback_enabled = 0;//manual mode
  nvram_data.motor_manulal_pwm_duty = MOTOR_DEFAULT_PWM_DUTY;
  nvram_data.motor_target_speed = MOTOR_DEFAULT_SPEED;
  
  nvram_data.flash_ok_flag = NVRAM_FLASH_OK_MASK;
}

void nvram_read_data(void)
{
  uint32_t address_src = FLASH_BASE + NVRAM_FLASH_SECTOR * FLASH_SECTOR_SIZE;
  flash_read(address_src, (uint8_t*)&nvram_data, sizeof(nvram_data));
  if (nvram_data.flash_ok_flag != NVRAM_FLASH_OK_MASK)
  {
    nvram_use_default_settings();
  }
}

// Save "nvram_data" to the Flash
void nvram_save_current_settings(void)
{
  flash_erase_sector(NVRAM_FLASH_SECTOR);
  uint32_t address_dst = FLASH_BASE + NVRAM_FLASH_SECTOR * FLASH_SECTOR_SIZE;
  flash_write(address_dst, (uint8_t*)&nvram_data, sizeof(nvram_data));
}


void nvram_prepare_and_save_current_settings(void)
{
  nvram_data.apd_voltage = apd_power_target_voltage;
  nvram_data.apd_manual_pwm = apd_power_pwm_manual_duty_value;
  nvram_data.apd_feedback_enabled = apd_power_feedback_en_flag;
  nvram_data.laser_voltage = current_laser_volt;
  nvram_data.comparator_voltage = apd_comp_threshold_mv;
  nvram_data.width_coef_a = dist_meas_width_coef_a;
  nvram_data.width_coef_b = dist_meas_width_coef_b;
  nvram_data.zero_offset_bin = dist_meas_zero_offset_bin;
  nvram_data.ref_obj_dist_mm = dist_meas_ref_dist_mm;
  nvram_data.tdc_bin_length = dist_meas_bin_length;
  
  nvram_data.motor_feedback_enabled = motor_ctrl_auto_speed_enabled;
  nvram_data.motor_manulal_pwm_duty = motor_ctrl_manual_pwm_duty;
  nvram_data.motor_target_speed = motor_ctrl_target_speed;
  
  nvram_save_current_settings();
}

