/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ENCODER_PROCESSING_H
#define __ENCODER_PROCESSING_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f30x.h"
#include "config.h"


/* Exported types ------------------------------------------------------------*/


/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void encoder_proc_init(void);
void encoder_proc_perodic_handling(void);


#endif /* __ENCODER_PROCESSING_H */
