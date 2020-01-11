//stm32f303cbt6
//32kb ram
//128kb flash
/* Includes ------------------------------------------------------------------*/
#include "main.h"

#include "nvram.h"
#include "hardware.h"
#include "apd_power.h"
#include "spi_driver.h"
#include "tdc_driver.h"
#include "uart_driver.h"
#include "dist_measurement.h"
#include "mavlink_handling.h"
#include "motor_controlling.h"
#include "encoder_processing.h"
#include "capture_controlling.h"

#include <stdio.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

// Variable to count 1 ms periods
uint32_t timer_1ms = 0;

// Variable to count 10 ms periods
uint32_t timer_10ms = 0;

// Variable to count 100 ms periods
uint32_t timer_100ms = 0;

float current_laser_volt = LASER_DEFAULT_VOLTAGE;

//Current comparator threshold voltage, mv
uint16_t apd_comp_threshold_mv = APD_COMP_DEFAULT_VOLT_MV;

uint16_t device_state_mask = 0;

extern uint8_t dist_meas_batch_measurement_needed;

/* Private function prototypes -----------------------------------------------*/
void measurement_cycle(void);
void load_nvram_values(void);

/* Private functions ---------------------------------------------------------*/

int main(void)
{  
  // Sysclk = 72 MHz
  hardware_init_all();
  nvram_read_data();
  load_nvram_values();
  
  apd_power_init_all();
  uart_driver_init();
  encoder_proc_init();
  
  init_tdc_periph();
  tdc_send_reset();
  tdc_test();
  
  motor_ctrl_init();
  capture_ctr_init();
  dist_measurement_init();
  tdc_configure();
  dwt_delay_ms(500);
  
  while (1)
  {
    if (TIMER_ELAPSED(timer_1ms))
    {
      START_TIMER(timer_1ms, 1);
      capture_ctr_data_processing();
      uart_driver_process();
      mavlink_long_packet_sending_process();
    }
    
    if (TIMER_ELAPSED(timer_10ms))
    {
      START_TIMER(timer_10ms, 10);

      apd_power_voltage_controlling();
      encoder_proc_perodic_handling();
    }
    
    if (TIMER_ELAPSED(timer_100ms))
    {
      START_TIMER(timer_100ms, 100);
      LED_GPIO->ODR^= LED_PIN;
      
      hardware_set_laser_voltage(current_laser_volt);
      hardware_set_apd_comp_voltage(apd_comp_threshold_mv);
      motor_ctrl_handling();
      dist_measurement_handler();
    }
  }
}

//Only "main.c" part
void load_nvram_values(void)
{
  current_laser_volt = nvram_data.laser_voltage;
  apd_comp_threshold_mv = nvram_data.comparator_voltage;
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif
