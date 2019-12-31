/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DIST_MEASUREMENT_H
#define __DIST_MEASUREMENT_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f30x.h"
#include "config.h"
#include "mavlink.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  uint16_t start_value;
  uint16_t width_value;
} tdc_point_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void dist_measurement_handler(void);
void dist_measurement_start_batch_meas(uint16_t size);
void dist_measurement_sync_capture_point(void);

#endif /* __DIST_MEASUREMENT_H */
