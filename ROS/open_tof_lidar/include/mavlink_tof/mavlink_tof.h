/** @file
 *  @brief MAVLink comm protocol generated from mavlink_tof.xml
 *  @see http://mavlink.org
 */
#pragma once
#ifndef MAVLINK_MAVLINK_TOF_H
#define MAVLINK_MAVLINK_TOF_H

#ifndef MAVLINK_H
    #error Wrong include order: MAVLINK_MAVLINK_TOF.H MUST NOT BE DIRECTLY USED. Include mavlink.h from the same directory instead or set ALL AND EVERY defines from MAVLINK.H manually accordingly, including the #define MAVLINK_H call.
#endif

#undef MAVLINK_THIS_XML_IDX
#define MAVLINK_THIS_XML_IDX 0

#ifdef __cplusplus
extern "C" {
#endif

// MESSAGE LENGTHS AND CRCS

#ifndef MAVLINK_MESSAGE_LENGTHS
#define MAVLINK_MESSAGE_LENGTHS {}
#endif

#ifndef MAVLINK_MESSAGE_CRCS
#define MAVLINK_MESSAGE_CRCS {{2, 157, 1, 0, 0, 0}, {3, 245, 5, 0, 0, 0}, {4, 188, 208, 0, 0, 0}, {100, 204, 6, 0, 0, 0}, {101, 160, 4, 0, 0, 0}, {102, 77, 2, 0, 0, 0}, {103, 121, 2, 0, 0, 0}, {104, 213, 2, 0, 0, 0}, {105, 227, 8, 0, 0, 0}, {106, 69, 2, 0, 0, 0}, {110, 216, 2, 0, 0, 0}, {111, 146, 4, 0, 0, 0}, {150, 42, 25, 0, 0, 0}, {151, 162, 14, 0, 0, 0}}
#endif

#include "../protocol.h"

#define MAVLINK_ENABLED_MAVLINK_TOF

// ENUM DEFINITIONS


/** @brief  */
#ifndef HAVE_ENUM_DATA_REQUEST
#define HAVE_ENUM_DATA_REQUEST
typedef enum DATA_REQUEST
{
   DATA_REQUEST_DEVICE_STATE=1, /* Request for device state | */
   DATA_REQUEST_MOTOR_STATE=2, /* Request for motor state | */
   DATA_REQUEST_ENUM_END=3, /*  | */
} DATA_REQUEST;
#endif

/** @brief  */
#ifndef HAVE_ENUM_DEVICE_COMMAND_TYPE
#define HAVE_ENUM_DEVICE_COMMAND_TYPE
typedef enum DEVICE_COMMAND_TYPE
{
   CMD_SAVE_TO_FLASH=1, /* Save configuration to Flash memory | */
   CMD_MCU_REBOOT=2, /* Reboot MCU | */
   DEVICE_COMMAND_TYPE_ENUM_END=3, /*  | */
} DEVICE_COMMAND_TYPE;
#endif

// MAVLINK VERSION

#ifndef MAVLINK_VERSION
#define MAVLINK_VERSION 1
#endif

#if (MAVLINK_VERSION == 0)
#undef MAVLINK_VERSION
#define MAVLINK_VERSION 1
#endif

// MESSAGE DEFINITIONS
#include "./mavlink_msg_data_request.h"
#include "./mavlink_msg_device_command.h"
#include "./mavlink_msg_long_packet.h"
#include "./mavlink_msg_set_apd_voltage.h"
#include "./mavlink_msg_set_laser_voltage.h"
#include "./mavlink_msg_set_comp_threshold.h"
#include "./mavlink_msg_start_batch_measurement.h"
#include "./mavlink_msg_start_corr_batch_measurement.h"
#include "./mavlink_msg_set_width_corr_coeff.h"
#include "./mavlink_msg_set_ref_offset.h"
#include "./mavlink_msg_set_motor_duty.h"
#include "./mavlink_msg_set_motor_speed.h"
#include "./mavlink_msg_device_state.h"
#include "./mavlink_msg_motor_state.h"

// base include


#undef MAVLINK_THIS_XML_IDX
#define MAVLINK_THIS_XML_IDX 0

#if MAVLINK_THIS_XML_IDX == MAVLINK_PRIMARY_XML_IDX
# define MAVLINK_MESSAGE_INFO {MAVLINK_MESSAGE_INFO_DATA_REQUEST, MAVLINK_MESSAGE_INFO_DEVICE_COMMAND, MAVLINK_MESSAGE_INFO_LONG_PACKET, MAVLINK_MESSAGE_INFO_SET_APD_VOLTAGE, MAVLINK_MESSAGE_INFO_SET_LASER_VOLTAGE, MAVLINK_MESSAGE_INFO_SET_COMP_THRESHOLD, MAVLINK_MESSAGE_INFO_START_BATCH_MEASUREMENT, MAVLINK_MESSAGE_INFO_START_CORR_BATCH_MEASUREMENT, MAVLINK_MESSAGE_INFO_SET_WIDTH_CORR_COEFF, MAVLINK_MESSAGE_INFO_SET_REF_OFFSET, MAVLINK_MESSAGE_INFO_SET_MOTOR_DUTY, MAVLINK_MESSAGE_INFO_SET_MOTOR_SPEED, MAVLINK_MESSAGE_INFO_DEVICE_STATE, MAVLINK_MESSAGE_INFO_MOTOR_STATE}
# define MAVLINK_MESSAGE_NAMES {{ "DATA_REQUEST", 2 }, { "DEVICE_COMMAND", 3 }, { "DEVICE_STATE", 150 }, { "LONG_PACKET", 4 }, { "MOTOR_STATE", 151 }, { "SET_APD_VOLTAGE", 100 }, { "SET_COMP_THRESHOLD", 102 }, { "SET_LASER_VOLTAGE", 101 }, { "SET_MOTOR_DUTY", 110 }, { "SET_MOTOR_SPEED", 111 }, { "SET_REF_OFFSET", 106 }, { "SET_WIDTH_CORR_COEFF", 105 }, { "START_BATCH_MEASUREMENT", 103 }, { "START_CORR_BATCH_MEASUREMENT", 104 }}
# if MAVLINK_COMMAND_24BIT
#  include "../mavlink_get_info.h"
# endif
#endif

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MAVLINK_MAVLINK_TOF_H
