/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HARDWARE_H
#define __HARDWARE_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f30x.h"
#include "config.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void hardware_init_all(void);
void dwt_delay_us(uint32_t us);
void hardware_set_laser_voltage(float voltage);
void hardware_set_apd_comp_voltage(uint16_t comp_threshold);
void dwt_delay_ms(uint32_t ms);

#endif /* __HARDWARE_H */
