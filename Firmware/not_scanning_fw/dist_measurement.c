/* Includes ------------------------------------------------------------------*/
#include "dist_measurement.h"
#include "hardware.h"
#include "mavlink.h"
#include "tdc_driver.h"
#include "mavlink_handling.h"
#include "nvram.h"
#include "config.h"


/* Private typedef -----------------------------------------------------------*/
typedef enum
{
  DIST_MEAS_REF_MEAS_IDLE = 0,
  DIST_MEAS_REF_MEAS_WAIT_FOR_START,
  DIST_MEAS_REF_MEAS_WAIT_FOR_BATCH,
  DIST_MEAS_REF_MEAS_PROCESS,
} dist_meas_ref_meas_state_t;

/* Private define ------------------------------------------------------------*/

// Max number of measured points in batch mode
#define DIST_MEAS_MAX_BATCH_POINTS      300

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
tdc_point_t tdc_capture_buf[DIST_MEAS_MAX_BATCH_POINTS];
uint8_t dist_meas_batch_measurement_needed = 0;

uint16_t dist_meas_batch_points = 100;//max is DIST_MEAS_MAX_BATCH_POINTS

//testing distance to an object in mm
uint16_t test_dist_value = 0;

// Distance to a reference object
uint16_t dist_meas_ref_dist_mm = 0;

// Zero offset, bins
uint16_t dist_meas_zero_offset_bin = 0;

dist_meas_ref_meas_state_t dist_meas_need_ref_measurement = 
  DIST_MEAS_REF_MEAS_IDLE;

// Width correction coefficient A
float dist_meas_width_coef_a = 0.0f;
  
// Width correction coefficient B
float dist_meas_width_coef_b = 0.0f;

// BIN length in mm
float dist_meas_bin_length = DEFAULT_DIST_BIN_LENGTH;

extern uint16_t tmp_res0;
extern uint16_t tmp_res1;
//extern uint8_t sync_pulses_enabled_flag;

/* Private function prototypes -----------------------------------------------*/
void dist_measurement_do_batch_meas(void);
void dist_measurement_calculate_zero_offset(uint16_t ref_dist_bin);
uint16_t dist_measurement_calc_avr_dist_bin(void);
void  dist_measurement_measure_ref_bins_handler(void);

/* Private functions ---------------------------------------------------------*/

void dist_measurement_init(void)
{
  dist_meas_width_coef_a = nvram_data.width_coef_a;
  dist_meas_width_coef_b = nvram_data.width_coef_b;
  dist_meas_zero_offset_bin = nvram_data.zero_offset_bin;
  dist_meas_ref_dist_mm = nvram_data.ref_obj_dist_mm;
  dist_meas_bin_length = nvram_data.tdc_bin_length;
}

//check if measurement needed
void dist_measurement_handler(void)
{
  if (dist_meas_batch_measurement_needed)
  {
    dist_measurement_do_batch_meas();
    mavlink_send_batch_data();
    dist_meas_batch_measurement_needed = DIST_MEAS_REF_MEAS_IDLE;
  }
  dist_measurement_measure_ref_bins_handler();
}

// Called by mavlink command
// This command only enables capture process
// It is done in "dist_measurement_do_batch_meas()"
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
    tdc_read_three_registers();
    
    tdc_capture_buf[i].start_value = tmp_res0;
    tdc_capture_buf[i].width_value = tmp_res1;
  }
}

//Start measurement the reference distance and zero offset
// dist_mm - real dist to ref object
void dist_measurement_start_measure_ref(uint16_t dist_mm)
{
  if (dist_meas_need_ref_measurement == DIST_MEAS_REF_MEAS_IDLE)
  {
    dist_meas_need_ref_measurement = DIST_MEAS_REF_MEAS_WAIT_FOR_START;
    dist_meas_ref_dist_mm = dist_mm;
  }
}

void  dist_measurement_measure_ref_bins_handler(void)
{
  if (dist_meas_need_ref_measurement == DIST_MEAS_REF_MEAS_WAIT_FOR_START)
  {
    dist_measurement_start_batch_meas(100);
    dist_meas_need_ref_measurement = DIST_MEAS_REF_MEAS_WAIT_FOR_BATCH;
  }
  else if (dist_meas_need_ref_measurement == DIST_MEAS_REF_MEAS_WAIT_FOR_BATCH)
  {
    if (dist_meas_batch_measurement_needed == 0) //data capture done
    {
      dist_meas_need_ref_measurement = DIST_MEAS_REF_MEAS_PROCESS;
      uint16_t avr_dist_bins = dist_measurement_calc_avr_dist_bin();
      
      avr_dist_bins = (uint16_t)round(dist_measurement_calc_corrected_dist_bin(
        avr_dist_bins, tmp_res1));//todo

      dist_measurement_calculate_zero_offset(avr_dist_bins);
      dist_meas_need_ref_measurement = DIST_MEAS_REF_MEAS_IDLE;
    }
  }
}

//Calculate average distance in bins
uint16_t dist_measurement_calc_avr_dist_bin(void)
{
  uint32_t summ = 0;
  
  //skip first point
  for (uint16_t i = 1; i < dist_meas_batch_points; i++)
  {
    summ += tdc_capture_buf[i].start_value;
  }
  return (summ / (dist_meas_batch_points - 1));
}

// We have: 
// 1. "ref_dist_bin" - distance to an object in bins
// 2. "dist_meas_ref_dist_mm" distance to an object in mm
//ref_dist_bin - corrected distance to a reference object, bin
void dist_measurement_calculate_zero_offset(uint16_t ref_dist_bin)
{
  // True distance in bins (with no offset)
  uint16_t true_dist_bin = 
    (uint16_t)roundf((float)dist_meas_ref_dist_mm / dist_meas_bin_length);
  
  if (ref_dist_bin > true_dist_bin)
    dist_meas_zero_offset_bin = ref_dist_bin - true_dist_bin;
  else
    dist_meas_zero_offset_bin = 0;
}

//testing function
void dist_measurement_process_current_data(void)
{
  float corr_dist_bin = 
    dist_measurement_calc_corrected_dist_bin(tmp_res0, tmp_res1);
  
  uint16_t dist_mm = dist_measurement_calc_dist(corr_dist_bin);
  test_dist_value = dist_mm;
}

// CORRECTIONS **********************************************************

// Return distance to an object in mm
uint16_t dist_measurement_calc_dist(float corr_dist_bin)
{
  float dist_mm = (corr_dist_bin - (float)dist_meas_zero_offset_bin) * dist_meas_bin_length;
  return (uint16_t)roundf(dist_mm);
}

// Calculate corrected distance in bins
// dist_bin - raw distance in bins
// width_bin - raw pulse width in bins
float dist_measurement_calc_corrected_dist_bin(
  uint16_t dist_bin, uint16_t width_bin)
{
  if (dist_meas_width_coef_a == 0.0f)
    return 0;
  
  float correction = exp((dist_meas_width_coef_a - (float)width_bin) / 
    dist_meas_width_coef_b);
  float result = roundf((float)dist_bin - correction);
  return (uint16_t)result;
}

//Change width correction coefficients
void dist_measurement_change_width_corr_coeff(
  mavlink_set_width_corr_coeff_t data_msg)
{
  if (data_msg.coeff_a == 0.0f)
    return;
  
  dist_meas_width_coef_a = data_msg.coeff_a;
  dist_meas_width_coef_b = data_msg.coeff_b;
}