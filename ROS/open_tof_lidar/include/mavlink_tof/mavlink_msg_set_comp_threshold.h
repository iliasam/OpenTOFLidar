#pragma once
// MESSAGE SET_COMP_THRESHOLD PACKING

#define MAVLINK_MSG_ID_SET_COMP_THRESHOLD 102

MAVPACKED(
typedef struct __mavlink_set_comp_threshold_t {
 uint16_t voltage_mv; /*< Comparator threshold voltage in mv*/
}) mavlink_set_comp_threshold_t;

#define MAVLINK_MSG_ID_SET_COMP_THRESHOLD_LEN 2
#define MAVLINK_MSG_ID_SET_COMP_THRESHOLD_MIN_LEN 2
#define MAVLINK_MSG_ID_102_LEN 2
#define MAVLINK_MSG_ID_102_MIN_LEN 2

#define MAVLINK_MSG_ID_SET_COMP_THRESHOLD_CRC 77
#define MAVLINK_MSG_ID_102_CRC 77



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SET_COMP_THRESHOLD { \
    102, \
    "SET_COMP_THRESHOLD", \
    1, \
    {  { "voltage_mv", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_set_comp_threshold_t, voltage_mv) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SET_COMP_THRESHOLD { \
    "SET_COMP_THRESHOLD", \
    1, \
    {  { "voltage_mv", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_set_comp_threshold_t, voltage_mv) }, \
         } \
}
#endif

/**
 * @brief Pack a set_comp_threshold message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param voltage_mv Comparator threshold voltage in mv
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_set_comp_threshold_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint16_t voltage_mv)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SET_COMP_THRESHOLD_LEN];
    _mav_put_uint16_t(buf, 0, voltage_mv);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SET_COMP_THRESHOLD_LEN);
#else
    mavlink_set_comp_threshold_t packet;
    packet.voltage_mv = voltage_mv;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SET_COMP_THRESHOLD_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SET_COMP_THRESHOLD;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SET_COMP_THRESHOLD_MIN_LEN, MAVLINK_MSG_ID_SET_COMP_THRESHOLD_LEN, MAVLINK_MSG_ID_SET_COMP_THRESHOLD_CRC);
}

/**
 * @brief Pack a set_comp_threshold message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param voltage_mv Comparator threshold voltage in mv
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_set_comp_threshold_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint16_t voltage_mv)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SET_COMP_THRESHOLD_LEN];
    _mav_put_uint16_t(buf, 0, voltage_mv);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SET_COMP_THRESHOLD_LEN);
#else
    mavlink_set_comp_threshold_t packet;
    packet.voltage_mv = voltage_mv;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SET_COMP_THRESHOLD_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SET_COMP_THRESHOLD;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SET_COMP_THRESHOLD_MIN_LEN, MAVLINK_MSG_ID_SET_COMP_THRESHOLD_LEN, MAVLINK_MSG_ID_SET_COMP_THRESHOLD_CRC);
}

/**
 * @brief Encode a set_comp_threshold struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param set_comp_threshold C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_set_comp_threshold_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_set_comp_threshold_t* set_comp_threshold)
{
    return mavlink_msg_set_comp_threshold_pack(system_id, component_id, msg, set_comp_threshold->voltage_mv);
}

/**
 * @brief Encode a set_comp_threshold struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param set_comp_threshold C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_set_comp_threshold_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_set_comp_threshold_t* set_comp_threshold)
{
    return mavlink_msg_set_comp_threshold_pack_chan(system_id, component_id, chan, msg, set_comp_threshold->voltage_mv);
}

/**
 * @brief Send a set_comp_threshold message
 * @param chan MAVLink channel to send the message
 *
 * @param voltage_mv Comparator threshold voltage in mv
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_set_comp_threshold_send(mavlink_channel_t chan, uint16_t voltage_mv)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SET_COMP_THRESHOLD_LEN];
    _mav_put_uint16_t(buf, 0, voltage_mv);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_COMP_THRESHOLD, buf, MAVLINK_MSG_ID_SET_COMP_THRESHOLD_MIN_LEN, MAVLINK_MSG_ID_SET_COMP_THRESHOLD_LEN, MAVLINK_MSG_ID_SET_COMP_THRESHOLD_CRC);
#else
    mavlink_set_comp_threshold_t packet;
    packet.voltage_mv = voltage_mv;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_COMP_THRESHOLD, (const char *)&packet, MAVLINK_MSG_ID_SET_COMP_THRESHOLD_MIN_LEN, MAVLINK_MSG_ID_SET_COMP_THRESHOLD_LEN, MAVLINK_MSG_ID_SET_COMP_THRESHOLD_CRC);
#endif
}

/**
 * @brief Send a set_comp_threshold message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_set_comp_threshold_send_struct(mavlink_channel_t chan, const mavlink_set_comp_threshold_t* set_comp_threshold)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_set_comp_threshold_send(chan, set_comp_threshold->voltage_mv);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_COMP_THRESHOLD, (const char *)set_comp_threshold, MAVLINK_MSG_ID_SET_COMP_THRESHOLD_MIN_LEN, MAVLINK_MSG_ID_SET_COMP_THRESHOLD_LEN, MAVLINK_MSG_ID_SET_COMP_THRESHOLD_CRC);
#endif
}

#if MAVLINK_MSG_ID_SET_COMP_THRESHOLD_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_set_comp_threshold_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint16_t voltage_mv)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint16_t(buf, 0, voltage_mv);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_COMP_THRESHOLD, buf, MAVLINK_MSG_ID_SET_COMP_THRESHOLD_MIN_LEN, MAVLINK_MSG_ID_SET_COMP_THRESHOLD_LEN, MAVLINK_MSG_ID_SET_COMP_THRESHOLD_CRC);
#else
    mavlink_set_comp_threshold_t *packet = (mavlink_set_comp_threshold_t *)msgbuf;
    packet->voltage_mv = voltage_mv;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_COMP_THRESHOLD, (const char *)packet, MAVLINK_MSG_ID_SET_COMP_THRESHOLD_MIN_LEN, MAVLINK_MSG_ID_SET_COMP_THRESHOLD_LEN, MAVLINK_MSG_ID_SET_COMP_THRESHOLD_CRC);
#endif
}
#endif

#endif

// MESSAGE SET_COMP_THRESHOLD UNPACKING


/**
 * @brief Get field voltage_mv from set_comp_threshold message
 *
 * @return Comparator threshold voltage in mv
 */
static inline uint16_t mavlink_msg_set_comp_threshold_get_voltage_mv(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Decode a set_comp_threshold message into a struct
 *
 * @param msg The message to decode
 * @param set_comp_threshold C-struct to decode the message contents into
 */
static inline void mavlink_msg_set_comp_threshold_decode(const mavlink_message_t* msg, mavlink_set_comp_threshold_t* set_comp_threshold)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    set_comp_threshold->voltage_mv = mavlink_msg_set_comp_threshold_get_voltage_mv(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SET_COMP_THRESHOLD_LEN? msg->len : MAVLINK_MSG_ID_SET_COMP_THRESHOLD_LEN;
        memset(set_comp_threshold, 0, MAVLINK_MSG_ID_SET_COMP_THRESHOLD_LEN);
    memcpy(set_comp_threshold, _MAV_PAYLOAD(msg), len);
#endif
}
