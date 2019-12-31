/* Includes ------------------------------------------------------------------*/
#include "stm32f3_flash.h"
#include "nvram.h"
#include "main.h"
#include "string.h"

/* Private typedef -----------------------------------------------------------*/
#define NVRAM_FLASH_OK_MASK     0xABCD

/* Private define ------------------------------------------------------------*/
//Number of the sector for storing data
#define NVRAM_FLASH_SECTOR      (((128 * FLASH_BYTES_PER_KB) / FLASH_SECTOR_SIZE) - 2)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
nvram_data_t nvram_data;

/* Private function prototypes -----------------------------------------------*/


/* Private functions ---------------------------------------------------------*/

void nvram_use_default_settings(void)
{
  nvram_data.apd_voltage = APD_DEFAULT_VOLTAGE;
  nvram_data.apd_manual_pwm = APD_DEFAULT_PWM_DUTY;
  nvram_data.apd_feedback_enabled = 0;//manual mode
  nvram_data.laser_voltage = LASER_DEFAULT_VOLTAGE;
  nvram_data.comparator_voltage = APD_COMP_DEFAULT_VOLT_MV;
  
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

