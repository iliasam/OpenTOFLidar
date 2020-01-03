#pragma once
// MESSAGE START_BATCH_MEASUREMENT PACKING

#define MAVLINK_MSG_ID_START_BATCH_MEASUREMENT 103

MAVPACKED(
typedef struct __mavlink_start_batch_measurement_t {
 uint16_t length; /*< Number of measurements*/
}) mavlink_start_batch_measurement_t;

#define MAVLINK_MSG_ID_START_BATCH_MEASUREMENT_LEN 2
#define MAVLINK_MSG_ID_START_BATCH_MEASUREMENT_MIN_LEN 2
#define MAVLINK_MSG_ID_103_LEN 2
#define MAVLINK_MSG_ID_103_MIN_LEN 2

#define MAVLINK_MSG_ID_START_BATCH_MEASUREMENT_CRC 121
#define MAVLINK_MSG_ID_103_CRC 121



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_START_BATCH_MEASUREMENT { \
    103, \
    "START_BATCH_MEASUREMENT", \
    1, \
    {  { "length", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_start_batch_measurement_t, length) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_START_BATCH_MEASUREMENT { \
    "START_BATCH_MEASUREMENT", \
    1, \
    {  { "length", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_start_batch_measurement_t, length) }, \
         } \
}
#endif

/**
 * @brief Pack a start_batch_measurement message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param length Number of measurements
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_start_batch_measurement_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint16_t length)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_START_BATCH_MEASUREMENT_LEN];
    _mav_put_uint16_t(buf, 0, length);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_START_BATCH_MEASUREMENT_LEN);
#else
    mavlink_start_batch_measurement_t packet;
    packet.length = length;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_START_BATCH_MEASUREMENT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_START_BATCH_MEASUREMENT;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_START_BATCH_MEASUREMENT_MIN_LEN, MAVLINK_MSG_ID_START_BATCH_MEASUREMENT_LEN, MAVLINK_MSG_ID_START_BATCH_MEASUREMENT_CRC);
}

/**
 * @brief Pack a start_batch_measurement message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param length Number of measurements
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_start_batch_measurement_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint16_t length)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_START_BATCH_MEASUREMENT_LEN];
    _mav_put_uint16_t(buf, 0, length);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_START_BATCH_MEASUREMENT_LEN);
#else
    mavlink_start_batch_measurement_t packet;
    packet.length = length;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_START_BATCH_MEASUREMENT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_START_BATCH_MEASUREMENT;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_START_BATCH_MEASUREMENT_MIN_LEN, MAVLINK_MSG_ID_START_BATCH_MEASUREMENT_LEN, MAVLINK_MSG_ID_START_BATCH_MEASUREMENT_CRC);
}

/**
 * @brief Encode a start_batch_measurement struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param start_batch_measurement C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_start_batch_measurement_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_start_batch_measurement_t* start_batch_measurement)
{
    return mavlink_msg_start_batch_measurement_pack(system_id, component_id, msg, start_batch_measurement->length);
}

/**
 * @brief Encode a start_batch_measurement struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param start_batch_measurement C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_start_batch_measurement_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_start_batch_measurement_t* start_batch_measurement)
{
    return mavlink_msg_start_batch_measurement_pack_chan(system_id, component_id, chan, msg, start_batch_measurement->length);
}

/**
 * @brief Send a start_batch_measurement message
 * @param chan MAVLink channel to send the message
 *
 * @param length Number of measurements
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_start_batch_measurement_send(mavlink_channel_t chan, uint16_t length)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_START_BATCH_MEASUREMENT_LEN];
    _mav_put_uint16_t(buf, 0, length);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_START_BATCH_MEASUREMENT, buf, MAVLINK_MSG_ID_START_BATCH_MEASUREMENT_MIN_LEN, MAVLINK_MSG_ID_START_BATCH_MEASUREMENT_LEN, MAVLINK_MSG_ID_START_BATCH_MEASUREMENT_CRC);
#else
    mavlink_start_batch_measurement_t packet;
    packet.length = length;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_START_BATCH_MEASUREMENT, (const char *)&packet, MAVLINK_MSG_ID_START_BATCH_MEASUREMENT_MIN_LEN, MAVLINK_MSG_ID_START_BATCH_MEASUREMENT_LEN, MAVLINK_MSG_ID_START_BATCH_MEASUREMENT_CRC);
#endif
}

/**
 * @brief Send a start_batch_measurement message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_start_batch_measurement_send_struct(mavlink_channel_t chan, const mavlink_start_batch_measurement_t* start_batch_measurement)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_start_batch_measurement_send(chan, start_batch_measurement->length);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_START_BATCH_MEASUREMENT, (const char *)start_batch_measurement, MAVLINK_MSG_ID_START_BATCH_MEASUREMENT_MIN_LEN, MAVLINK_MSG_ID_START_BATCH_MEASUREMENT_LEN, MAVLINK_MSG_ID_START_BATCH_MEASUREMENT_CRC);
#endif
}

#if MAVLINK_MSG_ID_START_BATCH_MEASUREMENT_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_start_batch_measurement_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint16_t length)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint16_t(buf, 0, length);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_START_BATCH_MEASUREMENT, buf, MAVLINK_MSG_ID_START_BATCH_MEASUREMENT_MIN_LEN, MAVLINK_MSG_ID_START_BATCH_MEASUREMENT_LEN, MAVLINK_MSG_ID_START_BATCH_MEASUREMENT_CRC);
#else
    mavlink_start_batch_measurement_t *packet = (mavlink_start_batch_measurement_t *)msgbuf;
    packet->length = length;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_START_BATCH_MEASUREMENT, (const char *)packet, MAVLINK_MSG_ID_START_BATCH_MEASUREMENT_MIN_LEN, MAVLINK_MSG_ID_START_BATCH_MEASUREMENT_LEN, MAVLINK_MSG_ID_START_BATCH_MEASUREMENT_CRC);
#endif
}
#endif

#endif

// MESSAGE START_BATCH_MEASUREMENT UNPACKING


/**
 * @brief Get field length from start_batch_measurement message
 *
 * @return Number of measurements
 */
static inline uint16_t mavlink_msg_start_batch_measurement_get_length(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Decode a start_batch_measurement message into a struct
 *
 * @param msg The message to decode
 * @param start_batch_measurement C-struct to decode the message contents into
 */
static inline void mavlink_msg_start_batch_measurement_decode(const mavlink_message_t* msg, mavlink_start_batch_measurement_t* start_batch_measurement)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    start_batch_measurement->length = mavlink_msg_start_batch_measurement_get_length(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_START_BATCH_MEASUREMENT_LEN? msg->len : MAVLINK_MSG_ID_START_BATCH_MEASUREMENT_LEN;
        memset(start_batch_measurement, 0, MAVLINK_MSG_ID_START_BATCH_MEASUREMENT_LEN);
    memcpy(start_batch_measurement, _MAV_PAYLOAD(msg), len);
#endif
}
