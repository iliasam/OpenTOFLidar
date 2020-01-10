/** @file
 *	@brief MAVLink comm protocol generated from mavlink_tof.xml
 *	@see http://mavlink.org
 */

#pragma once

#include <array>
#include <cstdint>
#include <sstream>

#ifndef MAVLINK_STX
#define MAVLINK_STX 253
#endif

#include "../message.hpp"

namespace mavlink {
namespace mavlink_tof {

/**
 * Array of msg_entry needed for @p mavlink_parse_char() (trought @p mavlink_get_msg_entry())
 */
constexpr std::array<mavlink_msg_entry_t, 14> MESSAGE_ENTRIES {{ {2, 157, 1, 0, 0, 0}, {3, 245, 5, 0, 0, 0}, {4, 188, 208, 0, 0, 0}, {100, 204, 6, 0, 0, 0}, {101, 160, 4, 0, 0, 0}, {102, 77, 2, 0, 0, 0}, {103, 121, 2, 0, 0, 0}, {104, 213, 2, 0, 0, 0}, {105, 227, 8, 0, 0, 0}, {106, 69, 2, 0, 0, 0}, {110, 216, 2, 0, 0, 0}, {111, 146, 4, 0, 0, 0}, {150, 42, 25, 0, 0, 0}, {151, 162, 14, 0, 0, 0} }};

//! MAVLINK VERSION
constexpr auto MAVLINK_VERSION = 1;


// ENUM DEFINITIONS


/** @brief  */
enum class DATA_REQUEST : uint8_t
{
    DEVICE_STATE=1, /* Request for device state | */
    MOTOR_STATE=2, /* Request for motor state | */
};

//! DATA_REQUEST ENUM_END
constexpr auto DATA_REQUEST_ENUM_END = 3;

/** @brief  */
enum class DEVICE_COMMAND_TYPE : uint8_t
{
    CMD_SAVE_TO_FLASH=1, /* Save configuration to Flash memory | */
    CMD_MCU_REBOOT=2, /* Reboot MCU | */
};

//! DEVICE_COMMAND_TYPE ENUM_END
constexpr auto DEVICE_COMMAND_TYPE_ENUM_END = 3;


} // namespace mavlink_tof
} // namespace mavlink

// MESSAGE DEFINITIONS
#include "./mavlink_msg_data_request.hpp"
#include "./mavlink_msg_device_command.hpp"
#include "./mavlink_msg_long_packet.hpp"
#include "./mavlink_msg_set_apd_voltage.hpp"
#include "./mavlink_msg_set_laser_voltage.hpp"
#include "./mavlink_msg_set_comp_threshold.hpp"
#include "./mavlink_msg_start_batch_measurement.hpp"
#include "./mavlink_msg_start_corr_batch_measurement.hpp"
#include "./mavlink_msg_set_width_corr_coeff.hpp"
#include "./mavlink_msg_set_ref_offset.hpp"
#include "./mavlink_msg_set_motor_duty.hpp"
#include "./mavlink_msg_set_motor_speed.hpp"
#include "./mavlink_msg_device_state.hpp"
#include "./mavlink_msg_motor_state.hpp"

// base include

