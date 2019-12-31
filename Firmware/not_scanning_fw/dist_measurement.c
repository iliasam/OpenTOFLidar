/* Includes ------------------------------------------------------------------*/
#include "dist_measurement.h"
#include "hardware.h"
#include "tdc_driver.h"
#include "mavlink_handling.h"


/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

// Max number of measured points in batch mode
#define DIST_MEAS_MAX_BATCH_POINTS       300

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
tdc_point_t tdc_capture_buf[DIST_MEAS_MAX_BATCH_POINTS];
uint8_t dist_meas_batch_measurement_needed = 0;

uint16_t dist_meas_batch_points = 100;//max is DIST_MEAS_MAX_BATCH_POINTS

//Batch capture in syncronous mode
uint8_t dist_meas_sync_capture_flag = 0;
uint16_t dist_meas_sync_captured_points = 0;//number of captured points

extern uint16_t tmp_res0;
extern uint16_t tmp_res1;

extern uint8_t sync_pulses_enabled_flag;

/* Private function prototypes -----------------------------------------------*/
void dist_measurement_do_batch_meas(void);

/* Private functions ---------------------------------------------------------*/

//check if measurement needed
void dist_measurement_handler(void)
{
  if (dist_meas_batch_measurement_needed)
  {
    dist_measurement_do_batch_meas();
    mavlink_send_batch_data();
    dist_meas_batch_measurement_needed = 0;
  }
}

// Called by mavlink command
// This command only enables racture process
// It is donne in "dist_measurement_do_batch_meas()"
void dist_measurement_start_batch_meas(uint16_t size)
{
  if (size > DIST_MEAS_MAX_BATCH_POINTS)
    size = DIST_MEAS_MAX_BATCH_POINTS;
  
  dist_meas_batch_measurement_needed = 1;
}

//Do batch measurement
// Called periodically form dist_measurement_handler()
void dist_measurement_do_batch_meas(void)
{
  for (uint16_t i = 0; i < dist_meas_batch_points; i++)
  {
    tdc_start_pulse();
    dwt_delay_ms(1);
    tdc_read_two_registers();
    
    tdc_capture_buf[i].start_value = tmp_res0;
    tdc_capture_buf[i].width_value = tmp_res1;
  }
}