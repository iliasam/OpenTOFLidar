/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MOTOR_CONTROLLING_H
#define __MOTOR_CONTROLLING_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f30x.h"
#include "config.h"


/* Exported types ------------------------------------------------------------*/


/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void motor_ctrl_handling(void);
void motor_ctrl_manual_set_pwm_duty(uint16_t duty);
void motor_ctrl_init(void);
void motor_ctrl_set_auto_speed(float speed);


#endif /* __MOTOR_CONTROLLING_H */
