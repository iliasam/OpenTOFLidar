#include "mavlink_handling.h"
#include "mavlink.h"
#include "uart_driver.h"
#include "apd_power.h"
#include "dist_measurement.h"
#include "nvram.h"

// Defines ********************************************************************
#define MAVLINK_TOF_SYS_ID              1 //system id

#define MAVLINK_TOF_COMP_ID             1 //component id

#define MAVLINK_LONG_PACKET_BATCH_CODE  1

typedef enum 
{
    // No tx
    MAVLINK_TX_BATCH_IDLE = 0,
    
    // Data is ready for tx
    MAVLINK_TX_BATCH_READY_TO_TX,
    
    // Process of tx is running
    MAVLINK_TX_BATCH_PROGRESS,
} mavlink_tx_batch_state_t;

typedef struct
{
    uint8_t data_code;
    uint16_t total_cnt;
    uint16_t packet_cnt;
    uint16_t current_packet_id;
    uint8_t* data_ptr;
    uint32_t total_data_size;//in bytes
} mavlink_long_packet_params_t;


// Variables ******************************************************************
extern float apd_power_voltage;
extern float apd_power_target_voltage;
extern float current_laser_volt;
extern uint16_t apd_comp_threshold_mv;
extern uint8_t apd_power_feedback_en_flag;
extern uint16_t device_state_mask;

extern uint16_t tmp_res0;//todo
extern uint16_t tmp_res1;
extern uint16_t test_dist_value;

extern tdc_point_t tdc_capture_buf[];
extern uint16_t dist_meas_batch_points;//max is DIST_MEAS_MAX_BATCH_POINTS

extern float dist_meas_bin_length;

mavlink_long_packet_params_t mavlink_long_packet_state;

mavlink_tx_batch_state_t mavlink_tx_batch_state = MAVLINK_TX_BATCH_IDLE;

mavlink_message_t mavlink_rx_msg;

// Functions ******************************************************************
uint8_t  mavlink_send_message(mavlink_message_t *msg);
void mavlink_send_device_state(void);
uint8_t mavlink_driver_try_send_subpacket(uint8_t *data, uint16_t cnt, uint16_t payload_size);

//Parse received byte (from PC)
void mavlink_parse_byte(uint8_t value)
{
  mavlink_status_t mavlink_status;
  
  if (mavlink_parse_char(0, value, &mavlink_rx_msg, &mavlink_status))
  {
    if (mavlink_rx_msg.msgid == MAVLINK_MSG_ID_DATA_REQUEST)
    {
      mavlink_data_request_t data_request_msg;
      mavlink_msg_data_request_decode(&mavlink_rx_msg, &data_request_msg);
      
      if (data_request_msg.data_type == DATA_REQUEST_DEVICE_STATE)
      {
        mavlink_send_device_state();
      }
    }
    if (mavlink_rx_msg.msgid == MAVLINK_MSG_ID_DEVICE_COMMAND)
    {
      mavlink_device_command_t device_command_msg;
      mavlink_msg_device_command_decode(&mavlink_rx_msg, &device_command_msg);
      
      if (device_command_msg.cmd == CMD_SAVE_TO_FLASH)
      {
        nvram_prepare_and_save_current_settings();
      }
      else if (device_command_msg.cmd == CMD_MCU_REBOOT)
      {
        NVIC_SystemReset();
      }
    }
    else if (mavlink_rx_msg.msgid == MAVLINK_MSG_ID_SET_LASER_VOLTAGE)
    {
      mavlink_set_laser_voltage_t data_msg;
      mavlink_msg_set_laser_voltage_decode(&mavlink_rx_msg, &data_msg);
      
      if (data_msg.voltage > 19)
        return;
      
      current_laser_volt = data_msg.voltage;
    }
    else if (mavlink_rx_msg.msgid == MAVLINK_MSG_ID_SET_APD_VOLTAGE)
    {
      mavlink_set_apd_voltage_t data_msg;
      mavlink_msg_set_apd_voltage_decode(&mavlink_rx_msg, &data_msg);
      
      apd_power_parse_new_setings(data_msg);
    }
    else if (mavlink_rx_msg.msgid == MAVLINK_MSG_ID_SET_COMP_THRESHOLD)
    {
      mavlink_set_comp_threshold_t data_msg;
      mavlink_msg_set_comp_threshold_decode(&mavlink_rx_msg, &data_msg);
      
      apd_comp_threshold_mv = data_msg.voltage_mv;
    }
    else if (mavlink_rx_msg.msgid == MAVLINK_MSG_ID_SET_BIN_LENGTH)
    {
      mavlink_set_bin_length_t data_msg;
      mavlink_msg_set_bin_length_decode(&mavlink_rx_msg, &data_msg);
      
      if ((data_msg.tdc_bin_length > 5.0f) && (data_msg.tdc_bin_length < 30.0f))
        dist_meas_bin_length = data_msg.tdc_bin_length;
    }
    else if (mavlink_rx_msg.msgid == MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF)
    {
      mavlink_set_width_corr_coeff_t data_msg;
      mavlink_msg_set_width_corr_coeff_decode(&mavlink_rx_msg, &data_msg);
      dist_measurement_change_width_corr_coeff(data_msg);
    }
    else if (mavlink_rx_msg.msgid == MAVLINK_MSG_ID_START_BATCH_MEASUREMENT)
    {
      mavlink_start_batch_measurement_t data_msg;
      mavlink_msg_start_batch_measurement_decode(&mavlink_rx_msg, &data_msg);
      
      dist_measurement_start_batch_meas(data_msg.length);
    }
    else if (mavlink_rx_msg.msgid == MAVLINK_MSG_ID_SET_REF_OFFSET)
    {
      mavlink_set_ref_offset_t data_msg;
      mavlink_msg_set_ref_offset_decode(&mavlink_rx_msg, &data_msg);
      dist_measurement_start_measure_ref(data_msg.dist_value);
    }
  }
}

void mavlink_send_device_state(void)
{
  mavlink_device_state_t device_state;
  device_state.apd_voltage_curr = apd_power_voltage;
  device_state.apd_voltage_targ = apd_power_target_voltage;
  device_state.las_voltage = current_laser_volt;
  device_state.voltage_mv = apd_comp_threshold_mv;
  device_state.pwm_value = APD_POWER_TIMER->APD_POWER_TIMER_PWM_REG;
  device_state.raw_tof_value = tmp_res0;
  device_state.raw_tof_width_value = tmp_res1;
  device_state.pwm_state = apd_power_feedback_en_flag;
  device_state.distance = test_dist_value;
  device_state.state = device_state_mask;
  device_state.tdc_bin_length = dist_meas_bin_length;
  
  mavlink_message_t mav_msg;

  mavlink_msg_device_state_encode(
            MAVLINK_TOF_SYS_ID,
            MAVLINK_TOF_COMP_ID,
            &mav_msg,
            &device_state);
  
  mavlink_send_message(&mav_msg);
}


// Send mavlink message (place it to tx fifo)
// Return 0 if addition fails
uint8_t mavlink_send_message(mavlink_message_t *msg)
{
    if (msg == NULL)
        return 0;
            
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t size = mavlink_msg_to_send_buffer(buffer, msg);
    if (size > MAVLINK_MAX_PACKET_LEN)
        return 0;
    return uart_driver_add_data_for_tx(buffer, size);
}


// Long packet sending by mavlink
void mavlink_long_packet_sending_process(void)
{
  if (mavlink_tx_batch_state == MAVLINK_TX_BATCH_PROGRESS)
  {
    if (mavlink_long_packet_state.packet_cnt < mavlink_long_packet_state.total_cnt)
    {
      // Calculate payload size
      uint8_t data_size = MAVLINK_MSG_LONG_PACKET_FIELD_DATA_LEN;
      if (mavlink_long_packet_state.packet_cnt == (mavlink_long_packet_state.total_cnt - 1)) //last packet
      {
        data_size = mavlink_long_packet_state.total_data_size % MAVLINK_MSG_LONG_PACKET_FIELD_DATA_LEN;
        if (data_size == 0)
        {
          data_size = MAVLINK_MSG_LONG_PACKET_FIELD_DATA_LEN;
        }
      }
      
      //Try to add data to fifo
      uint8_t res = mavlink_driver_try_send_subpacket(
        mavlink_long_packet_state.data_ptr, 
        mavlink_long_packet_state.packet_cnt, data_size);
      
      if (res == 0)
      {
        return;
      }
      else
      {
        mavlink_long_packet_state.data_ptr += data_size;
        mavlink_long_packet_state.packet_cnt++;
      }
    }
    else
    {
      // All packets are sent
      mavlink_tx_batch_state = MAVLINK_TX_BATCH_IDLE;
    }
  }
}

// Try to send part of the long packet
// return 0 if can't send packet
uint8_t mavlink_driver_try_send_subpacket(uint8_t *data, uint16_t cnt, uint16_t payload_size)
{
    mavlink_long_packet_t long_packet_msg;
    long_packet_msg.data_code = mavlink_long_packet_state.data_code;
    long_packet_msg.total_cnt = mavlink_long_packet_state.total_cnt;
    long_packet_msg.packet_id = mavlink_long_packet_state.current_packet_id;
    long_packet_msg.payload_size = payload_size;
    long_packet_msg.packet_cnt = mavlink_long_packet_state.packet_cnt;
    memcpy(&long_packet_msg.data[0], data, MAVLINK_MSG_LONG_PACKET_FIELD_DATA_LEN);
    
    mavlink_message_t tmp_msg;
    mavlink_msg_long_packet_encode(
            MAVLINK_TOF_SYS_ID,
            MAVLINK_TOF_COMP_ID,
            &tmp_msg,
            &long_packet_msg);
    return mavlink_send_message(&tmp_msg);
}

//send batch data
void mavlink_send_batch_data(void)
{
  /*
  if (mavlink_driver_tx_single_photo_state != MAVLINK_DRIVER_TX_SINGLE_IDLE)
  {
  //ставим в очередь
  mavlink_driver_single_hist_request_pending = MAVLINK_DRIVER_PACKET_QUEUE_WAIT;
  return;
}
  */
  
  // Prepare long packet for tx
  mavlink_tx_batch_state = MAVLINK_TX_BATCH_READY_TO_TX;
  mavlink_long_packet_state.data_code = MAVLINK_LONG_PACKET_BATCH_CODE;
  mavlink_long_packet_state.data_ptr = (uint8_t*)&tdc_capture_buf[0];
  mavlink_long_packet_state.current_packet_id++;
  
  // Округлить к большему
  mavlink_long_packet_state.total_data_size = dist_meas_batch_points * sizeof(tdc_point_t);
  mavlink_long_packet_state.total_cnt = 
    (dist_meas_batch_points * sizeof(tdc_point_t) + MAVLINK_MSG_LONG_PACKET_FIELD_DATA_LEN - 1) / 
      MAVLINK_MSG_LONG_PACKET_FIELD_DATA_LEN;
  
  mavlink_long_packet_state.packet_cnt = 0;
  mavlink_tx_batch_state = MAVLINK_TX_BATCH_PROGRESS;
  //mavlink_driver_single_hist_request_pending = MAVLINK_DRIVER_PACKET_IDLE;
}
