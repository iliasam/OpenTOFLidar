#pragma once
// MESSAGE SET_BIN_LENGTH PACKING

#define MAVLINK_MSG_ID_SET_BIN_LENGTH 112

MAVPACKED(
typedef struct __mavlink_set_bin_length_t {
 float tdc_bin_length; /*< BIN length in mm*/
}) mavlink_set_bin_length_t;

#define MAVLINK_MSG_ID_SET_BIN_LENGTH_LEN 4
#define MAVLINK_MSG_ID_SET_BIN_LENGTH_MIN_LEN 4
#define MAVLINK_MSG_ID_112_LEN 4
#define MAVLINK_MSG_ID_112_MIN_LEN 4

#define MAVLINK_MSG_ID_SET_BIN_LENGTH_CRC 106
#define MAVLINK_MSG_ID_112_CRC 106



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SET_BIN_LENGTH { \
    112, \
    "SET_BIN_LENGTH", \
    1, \
    {  { "tdc_bin_length", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_set_bin_length_t, tdc_bin_length) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SET_BIN_LENGTH { \
    "SET_BIN_LENGTH", \
    1, \
    {  { "tdc_bin_length", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_set_bin_length_t, tdc_bin_length) }, \
         } \
}
#endif

/**
 * @brief Pack a set_bin_length message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param tdc_bin_length BIN length in mm
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_set_bin_length_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float tdc_bin_length)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SET_BIN_LENGTH_LEN];
    _mav_put_float(buf, 0, tdc_bin_length);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SET_BIN_LENGTH_LEN);
#else
    mavlink_set_bin_length_t packet;
    packet.tdc_bin_length = tdc_bin_length;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SET_BIN_LENGTH_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SET_BIN_LENGTH;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SET_BIN_LENGTH_MIN_LEN, MAVLINK_MSG_ID_SET_BIN_LENGTH_LEN, MAVLINK_MSG_ID_SET_BIN_LENGTH_CRC);
}

/**
 * @brief Pack a set_bin_length message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param tdc_bin_length BIN length in mm
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_set_bin_length_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float tdc_bin_length)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SET_BIN_LENGTH_LEN];
    _mav_put_float(buf, 0, tdc_bin_length);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SET_BIN_LENGTH_LEN);
#else
    mavlink_set_bin_length_t packet;
    packet.tdc_bin_length = tdc_bin_length;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SET_BIN_LENGTH_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SET_BIN_LENGTH;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SET_BIN_LENGTH_MIN_LEN, MAVLINK_MSG_ID_SET_BIN_LENGTH_LEN, MAVLINK_MSG_ID_SET_BIN_LENGTH_CRC);
}

/**
 * @brief Encode a set_bin_length struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param set_bin_length C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_set_bin_length_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_set_bin_length_t* set_bin_length)
{
    return mavlink_msg_set_bin_length_pack(system_id, component_id, msg, set_bin_length->tdc_bin_length);
}

/**
 * @brief Encode a set_bin_length struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param set_bin_length C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_set_bin_length_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_set_bin_length_t* set_bin_length)
{
    return mavlink_msg_set_bin_length_pack_chan(system_id, component_id, chan, msg, set_bin_length->tdc_bin_length);
}

/**
 * @brief Send a set_bin_length message
 * @param chan MAVLink channel to send the message
 *
 * @param tdc_bin_length BIN length in mm
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_set_bin_length_send(mavlink_channel_t chan, float tdc_bin_length)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SET_BIN_LENGTH_LEN];
    _mav_put_float(buf, 0, tdc_bin_length);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_BIN_LENGTH, buf, MAVLINK_MSG_ID_SET_BIN_LENGTH_MIN_LEN, MAVLINK_MSG_ID_SET_BIN_LENGTH_LEN, MAVLINK_MSG_ID_SET_BIN_LENGTH_CRC);
#else
    mavlink_set_bin_length_t packet;
    packet.tdc_bin_length = tdc_bin_length;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_BIN_LENGTH, (const char *)&packet, MAVLINK_MSG_ID_SET_BIN_LENGTH_MIN_LEN, MAVLINK_MSG_ID_SET_BIN_LENGTH_LEN, MAVLINK_MSG_ID_SET_BIN_LENGTH_CRC);
#endif
}

/**
 * @brief Send a set_bin_length message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_set_bin_length_send_struct(mavlink_channel_t chan, const mavlink_set_bin_length_t* set_bin_length)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_set_bin_length_send(chan, set_bin_length->tdc_bin_length);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_BIN_LENGTH, (const char *)set_bin_length, MAVLINK_MSG_ID_SET_BIN_LENGTH_MIN_LEN, MAVLINK_MSG_ID_SET_BIN_LENGTH_LEN, MAVLINK_MSG_ID_SET_BIN_LENGTH_CRC);
#endif
}

#if MAVLINK_MSG_ID_SET_BIN_LENGTH_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_set_bin_length_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float tdc_bin_length)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, tdc_bin_length);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_BIN_LENGTH, buf, MAVLINK_MSG_ID_SET_BIN_LENGTH_MIN_LEN, MAVLINK_MSG_ID_SET_BIN_LENGTH_LEN, MAVLINK_MSG_ID_SET_BIN_LENGTH_CRC);
#else
    mavlink_set_bin_length_t *packet = (mavlink_set_bin_length_t *)msgbuf;
    packet->tdc_bin_length = tdc_bin_length;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_BIN_LENGTH, (const char *)packet, MAVLINK_MSG_ID_SET_BIN_LENGTH_MIN_LEN, MAVLINK_MSG_ID_SET_BIN_LENGTH_LEN, MAVLINK_MSG_ID_SET_BIN_LENGTH_CRC);
#endif
}
#endif

#endif

// MESSAGE SET_BIN_LENGTH UNPACKING


/**
 * @brief Get field tdc_bin_length from set_bin_length message
 *
 * @return BIN length in mm
 */
static inline float mavlink_msg_set_bin_length_get_tdc_bin_length(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Decode a set_bin_length message into a struct
 *
 * @param msg The message to decode
 * @param set_bin_length C-struct to decode the message contents into
 */
static inline void mavlink_msg_set_bin_length_decode(const mavlink_message_t* msg, mavlink_set_bin_length_t* set_bin_length)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    set_bin_length->tdc_bin_length = mavlink_msg_set_bin_length_get_tdc_bin_length(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SET_BIN_LENGTH_LEN? msg->len : MAVLINK_MSG_ID_SET_BIN_LENGTH_LEN;
        memset(set_bin_length, 0, MAVLINK_MSG_ID_SET_BIN_LENGTH_LEN);
    memcpy(set_bin_length, _MAV_PAYLOAD(msg), len);
#endif
}
