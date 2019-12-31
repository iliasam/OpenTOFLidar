#pragma once
// MESSAGE DEVICE_COMMAND PACKING

#define MAVLINK_MSG_ID_DEVICE_COMMAND 3

MAVPACKED(
typedef struct __mavlink_device_command_t {
 uint32_t value; /*< Additional value*/
 uint8_t cmd; /*< Command*/
}) mavlink_device_command_t;

#define MAVLINK_MSG_ID_DEVICE_COMMAND_LEN 5
#define MAVLINK_MSG_ID_DEVICE_COMMAND_MIN_LEN 5
#define MAVLINK_MSG_ID_3_LEN 5
#define MAVLINK_MSG_ID_3_MIN_LEN 5

#define MAVLINK_MSG_ID_DEVICE_COMMAND_CRC 245
#define MAVLINK_MSG_ID_3_CRC 245



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_DEVICE_COMMAND { \
    3, \
    "DEVICE_COMMAND", \
    2, \
    {  { "cmd", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_device_command_t, cmd) }, \
         { "value", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_device_command_t, value) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_DEVICE_COMMAND { \
    "DEVICE_COMMAND", \
    2, \
    {  { "cmd", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_device_command_t, cmd) }, \
         { "value", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_device_command_t, value) }, \
         } \
}
#endif

/**
 * @brief Pack a device_command message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param cmd Command
 * @param value Additional value
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_device_command_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t cmd, uint32_t value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DEVICE_COMMAND_LEN];
    _mav_put_uint32_t(buf, 0, value);
    _mav_put_uint8_t(buf, 4, cmd);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DEVICE_COMMAND_LEN);
#else
    mavlink_device_command_t packet;
    packet.value = value;
    packet.cmd = cmd;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DEVICE_COMMAND_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_DEVICE_COMMAND;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_DEVICE_COMMAND_MIN_LEN, MAVLINK_MSG_ID_DEVICE_COMMAND_LEN, MAVLINK_MSG_ID_DEVICE_COMMAND_CRC);
}

/**
 * @brief Pack a device_command message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param cmd Command
 * @param value Additional value
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_device_command_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t cmd,uint32_t value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DEVICE_COMMAND_LEN];
    _mav_put_uint32_t(buf, 0, value);
    _mav_put_uint8_t(buf, 4, cmd);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DEVICE_COMMAND_LEN);
#else
    mavlink_device_command_t packet;
    packet.value = value;
    packet.cmd = cmd;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DEVICE_COMMAND_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_DEVICE_COMMAND;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_DEVICE_COMMAND_MIN_LEN, MAVLINK_MSG_ID_DEVICE_COMMAND_LEN, MAVLINK_MSG_ID_DEVICE_COMMAND_CRC);
}

/**
 * @brief Encode a device_command struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param device_command C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_device_command_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_device_command_t* device_command)
{
    return mavlink_msg_device_command_pack(system_id, component_id, msg, device_command->cmd, device_command->value);
}

/**
 * @brief Encode a device_command struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param device_command C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_device_command_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_device_command_t* device_command)
{
    return mavlink_msg_device_command_pack_chan(system_id, component_id, chan, msg, device_command->cmd, device_command->value);
}

/**
 * @brief Send a device_command message
 * @param chan MAVLink channel to send the message
 *
 * @param cmd Command
 * @param value Additional value
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_device_command_send(mavlink_channel_t chan, uint8_t cmd, uint32_t value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DEVICE_COMMAND_LEN];
    _mav_put_uint32_t(buf, 0, value);
    _mav_put_uint8_t(buf, 4, cmd);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DEVICE_COMMAND, buf, MAVLINK_MSG_ID_DEVICE_COMMAND_MIN_LEN, MAVLINK_MSG_ID_DEVICE_COMMAND_LEN, MAVLINK_MSG_ID_DEVICE_COMMAND_CRC);
#else
    mavlink_device_command_t packet;
    packet.value = value;
    packet.cmd = cmd;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DEVICE_COMMAND, (const char *)&packet, MAVLINK_MSG_ID_DEVICE_COMMAND_MIN_LEN, MAVLINK_MSG_ID_DEVICE_COMMAND_LEN, MAVLINK_MSG_ID_DEVICE_COMMAND_CRC);
#endif
}

/**
 * @brief Send a device_command message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_device_command_send_struct(mavlink_channel_t chan, const mavlink_device_command_t* device_command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_device_command_send(chan, device_command->cmd, device_command->value);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DEVICE_COMMAND, (const char *)device_command, MAVLINK_MSG_ID_DEVICE_COMMAND_MIN_LEN, MAVLINK_MSG_ID_DEVICE_COMMAND_LEN, MAVLINK_MSG_ID_DEVICE_COMMAND_CRC);
#endif
}

#if MAVLINK_MSG_ID_DEVICE_COMMAND_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_device_command_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t cmd, uint32_t value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, value);
    _mav_put_uint8_t(buf, 4, cmd);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DEVICE_COMMAND, buf, MAVLINK_MSG_ID_DEVICE_COMMAND_MIN_LEN, MAVLINK_MSG_ID_DEVICE_COMMAND_LEN, MAVLINK_MSG_ID_DEVICE_COMMAND_CRC);
#else
    mavlink_device_command_t *packet = (mavlink_device_command_t *)msgbuf;
    packet->value = value;
    packet->cmd = cmd;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DEVICE_COMMAND, (const char *)packet, MAVLINK_MSG_ID_DEVICE_COMMAND_MIN_LEN, MAVLINK_MSG_ID_DEVICE_COMMAND_LEN, MAVLINK_MSG_ID_DEVICE_COMMAND_CRC);
#endif
}
#endif

#endif

// MESSAGE DEVICE_COMMAND UNPACKING


/**
 * @brief Get field cmd from device_command message
 *
 * @return Command
 */
static inline uint8_t mavlink_msg_device_command_get_cmd(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Get field value from device_command message
 *
 * @return Additional value
 */
static inline uint32_t mavlink_msg_device_command_get_value(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Decode a device_command message into a struct
 *
 * @param msg The message to decode
 * @param device_command C-struct to decode the message contents into
 */
static inline void mavlink_msg_device_command_decode(const mavlink_message_t* msg, mavlink_device_command_t* device_command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    device_command->value = mavlink_msg_device_command_get_value(msg);
    device_command->cmd = mavlink_msg_device_command_get_cmd(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_DEVICE_COMMAND_LEN? msg->len : MAVLINK_MSG_ID_DEVICE_COMMAND_LEN;
        memset(device_command, 0, MAVLINK_MSG_ID_DEVICE_COMMAND_LEN);
    memcpy(device_command, _MAV_PAYLOAD(msg), len);
#endif
}
