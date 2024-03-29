#include "mavlink_handling.h"
#include "mavlink.h"
#include "uart_driver.h"
#include "apd_power.h"
#include "dist_measurement.h"
#include "motor_controlling.h"
#include "nvram.h"
#include "main.h"

// Defines ********************************************************************
#define MAVLINK_TOF_SYS_ID              1 //system id

#define MAVLINK_TOF_COMP_ID             1 //component id

// Batch capture data 
#define MAVLINK_LONG_PACKET_BATCH_CODE  1

// Scan capture data 
#define MAVLINK_LONG_PACKET_SCAN_CODE   2

#define MAVLINK_UART_BUSY_TIMEOUT_MS    1000

typedef enum 
{
    // No tx
    MAVLINK_TX_BATCH_IDLE = 0,
    
    // Data is ready for tx
    MAVLINK_TX_BATCH_READY_TO_TX,
    
    // Process of tx is running
    MAVLINK_TX_BATCH_PROGRESS,
} mavlink_tx_batch_state_t;

typedef enum 
{
    // No tx
    MAVLINK_TX_SCAN_IDLE = 0,
    
    // Data is ready for tx
    MAVLINK_TX_SCAN_READY_TO_TX,
    
    // Process of tx is running
    MAVLINK_TX_SCN_PROGRESS,
} mavlink_tx_scan_state_t;

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
extern float dist_meas_bin_length;

extern uint16_t tmp_res0;//todo
extern uint16_t tmp_res1;
extern uint16_t test_dist_value;

extern float motor_ctrl_current_speed;
extern uint16_t motor_ctrl_current_pwm_duty;
extern uint16_t motor_ctrl_manual_pwm_duty;
extern float motor_ctrl_target_speed;

extern tdc_point_t tdc_capture_buf[];
extern uint16_t dist_meas_batch_points;//max is DIST_MEAS_MAX_BATCH_POINTS

mavlink_long_packet_params_t mavlink_long_packet_state;

mavlink_tx_scan_state_t  mavlink_tx_scan_state = MAVLINK_TX_SCAN_IDLE;

// Flag - long packet tx is active
uint8_t mavlink_long_packet_tx_active = 0;

mavlink_message_t mavlink_rx_msg;

//Set when MCU is trying to send packet while UART is busy
uint32_t mavlink_busy_timestamp = 0xFFFFFFF;

// Functions ******************************************************************
uint8_t  mavlink_send_message(mavlink_message_t *msg);
void mavlink_send_device_state(void);
void mavlink_send_motor_state(void);
uint8_t mavlink_driver_try_send_subpacket(uint8_t *data, uint16_t cnt, uint16_t payload_size);


void mavlink_parse_byte(uint8_t value)
{
  static mavlink_status_t mavlink_status;
  
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
      else if (data_request_msg.data_type == DATA_REQUEST_MOTOR_STATE)
      {
        mavlink_send_motor_state();
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
      
      if ((data_msg.tdc_bin_length > 5.0f) && 
          (data_msg.tdc_bin_length < MAX_BIN_LENGTH_MM))
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
    else if (mavlink_rx_msg.msgid == MAVLINK_MSG_ID_SET_MOTOR_DUTY)
    {
      mavlink_set_motor_duty_t data_msg;
      mavlink_msg_set_motor_duty_decode(&mavlink_rx_msg, &data_msg);
      motor_ctrl_manual_set_pwm_duty(data_msg.duty);
    }
    else if (mavlink_rx_msg.msgid == MAVLINK_MSG_ID_SET_MOTOR_SPEED)
    {
      mavlink_set_motor_speed_t data_msg;
      mavlink_msg_set_motor_speed_decode(&mavlink_rx_msg, &data_msg);
      motor_ctrl_set_auto_speed(data_msg.speed);
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

void mavlink_send_motor_state(void)
{
  mavlink_motor_state_t motor_state;
  motor_state.motor_speed = motor_ctrl_current_speed;
  motor_state.pwm_duty = motor_ctrl_current_pwm_duty;
  motor_state.setted_pwm_duty = motor_ctrl_manual_pwm_duty;
  motor_state.setted_motor_speed = motor_ctrl_target_speed;
  motor_state.state = device_state_mask;
  
  mavlink_message_t mav_msg;

  mavlink_msg_motor_state_encode(
            MAVLINK_TOF_SYS_ID,
            MAVLINK_TOF_COMP_ID,
            &mav_msg,
            &motor_state);
  
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
  uint32_t curr_time_ms;
  START_TIMER(curr_time_ms, 0);
  uint32_t diff_ms = curr_time_ms - mavlink_busy_timestamp;
  if ((diff_ms > MAVLINK_UART_BUSY_TIMEOUT_MS) || 
      (mavlink_busy_timestamp > curr_time_ms))
  {
    device_state_mask &= ~UART_BUSY_FLAG;
  }
  else
    device_state_mask |= UART_BUSY_FLAG;
  
  if (mavlink_long_packet_tx_active != 0)
  {
    if (mavlink_long_packet_state.packet_cnt < mavlink_long_packet_state.total_cnt)
    {
      // Calculate payload size
      uint8_t data_size = MAVLINK_MSG_LONG_PACKET_FIELD_DATA_LEN;
      if (mavlink_long_packet_state.packet_cnt == 
          (mavlink_long_packet_state.total_cnt - 1)) //last packet
      {
        data_size = mavlink_long_packet_state.total_data_size % 
          MAVLINK_MSG_LONG_PACKET_FIELD_DATA_LEN;
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
      mavlink_long_packet_tx_active = 0;
    }
  }
}

// Try to send part of the long packet
// return 0 if can't send packet
uint8_t mavlink_driver_try_send_subpacket(
  uint8_t *data, uint16_t cnt, uint16_t payload_size)
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
  if (mavlink_long_packet_tx_active)
  {
    START_TIMER(mavlink_busy_timestamp, 0);
    return;
  }
  
  // Prepare long packet for tx
  mavlink_long_packet_state.data_code = MAVLINK_LONG_PACKET_BATCH_CODE;
  mavlink_long_packet_state.data_ptr = (uint8_t*)&tdc_capture_buf[0];
  mavlink_long_packet_state.current_packet_id++;
  
  // Round to bigger value
  mavlink_long_packet_state.total_data_size = 
    dist_meas_batch_points * sizeof(tdc_point_t);
  mavlink_long_packet_state.total_cnt = 
    (dist_meas_batch_points * sizeof(tdc_point_t) + 
     MAVLINK_MSG_LONG_PACKET_FIELD_DATA_LEN - 1) / 
      MAVLINK_MSG_LONG_PACKET_FIELD_DATA_LEN;
  
  mavlink_long_packet_state.packet_cnt = 0;
  mavlink_long_packet_tx_active = 1;
}

// send scan data
// points_cnt - number of captured point, not bytes
void mavlink_send_scan_data(uint16_t* data_source, uint16_t points_cnt)
{
  if (mavlink_long_packet_tx_active)
  {
    START_TIMER(mavlink_busy_timestamp, 0);
    return;
  }
  
  // Prepare long packet for tx
  mavlink_long_packet_state.data_code = MAVLINK_LONG_PACKET_SCAN_CODE;
  mavlink_long_packet_state.data_ptr = (uint8_t*)data_source;
  mavlink_long_packet_state.current_packet_id++;
  
  // Round to bigger value
  mavlink_long_packet_state.total_data_size = points_cnt * sizeof(uint16_t);
  mavlink_long_packet_state.total_cnt = 
    (points_cnt * sizeof(uint16_t) + MAVLINK_MSG_LONG_PACKET_FIELD_DATA_LEN - 1) / 
      MAVLINK_MSG_LONG_PACKET_FIELD_DATA_LEN;
  
  mavlink_long_packet_state.packet_cnt = 0;
  mavlink_long_packet_tx_active = 1;
}
