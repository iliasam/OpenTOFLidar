/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DIST_MEASUREMENT_H
#define __DIST_MEASUREMENT_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f30x.h"
#include "config.h"
#include "mavlink.h"
#include "tdc_driver.h"

/* Exported types ------------------------------------------------------------*/

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
uint16_t dist_measurement_process_current_data(void);
void dist_measurement_start_measure_ref(uint16_t dist_mm);
uint16_t dist_measurement_process_data(uint16_t start, uint16_t width);
void dist_measurement_update_ref_value(tdc_point_t ref_dist);

#endif /* __DIST_MEASUREMENT_H */
