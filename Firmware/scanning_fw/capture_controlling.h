/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CAPTURE_CONTROLLING_H
#define __CAPTURE_CONTROLLING_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f30x.h"
#include "config.h"

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void capture_ctr_init(void);
void capture_ctr_encoder_event(uint16_t event_cnt, uint16_t last_period);
void capture_ctr_encoder_zero_event(void);
void capture_ctr_data_processing(void);


#endif /* __CAPTURE_CONTROLLING_H */
