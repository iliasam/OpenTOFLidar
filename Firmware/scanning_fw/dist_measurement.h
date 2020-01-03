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
void dist_measurement_init(void);

void dist_measurement_change_width_corr_coeff(
  mavlink_set_width_corr_coeff_t data_msg);
uint16_t dist_measurement_calc_dist(float corr_dist_bin);
float dist_measurement_calc_corrected_dist_bin(
  uint16_t dist_bin, uint16_t width_bin);
void dist_measurement_process_current_data(void);
void dist_measurement_start_measure_ref(uint16_t dist_mm);

#endif /* __DIST_MEASUREMENT_H */
