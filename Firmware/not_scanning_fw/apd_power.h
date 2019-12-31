/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APD_POWER_H
#define __APD_POWER_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f30x.h"
#include "config.h"
#include "mavlink.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void apd_power_timer_init(void);
void apd_power_timer_activate_pwm(void);
void apd_power_init_all(void);
void apd_power_voltage_controlling(void);

void apd_power_parse_new_setings(mavlink_set_apd_voltage_t msg);

#endif /* __APD_POWER_H */
