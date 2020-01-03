#pragma once
// MESSAGE SET_WIDTH_CORR_COEFF PACKING

#define MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF 105

MAVPACKED(
typedef struct __mavlink_set_width_corr_coeff_t {
 float coeff_a; /*< Coefficient A*/
 float coeff_b; /*< Coefficient B*/
}) mavlink_set_width_corr_coeff_t;

#define MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF_LEN 8
#define MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF_MIN_LEN 8
#define MAVLINK_MSG_ID_105_LEN 8
#define MAVLINK_MSG_ID_105_MIN_LEN 8

#define MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF_CRC 227
#define MAVLINK_MSG_ID_105_CRC 227



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SET_WIDTH_CORR_COEFF { \
    105, \
    "SET_WIDTH_CORR_COEFF", \
    2, \
    {  { "coeff_a", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_set_width_corr_coeff_t, coeff_a) }, \
         { "coeff_b", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_set_width_corr_coeff_t, coeff_b) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SET_WIDTH_CORR_COEFF { \
    "SET_WIDTH_CORR_COEFF", \
    2, \
    {  { "coeff_a", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_set_width_corr_coeff_t, coeff_a) }, \
         { "coeff_b", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_set_width_corr_coeff_t, coeff_b) }, \
         } \
}
#endif

/**
 * @brief Pack a set_width_corr_coeff message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param coeff_a Coefficient A
 * @param coeff_b Coefficient B
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_set_width_corr_coeff_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float coeff_a, float coeff_b)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF_LEN];
    _mav_put_float(buf, 0, coeff_a);
    _mav_put_float(buf, 4, coeff_b);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF_LEN);
#else
    mavlink_set_width_corr_coeff_t packet;
    packet.coeff_a = coeff_a;
    packet.coeff_b = coeff_b;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF_MIN_LEN, MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF_LEN, MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF_CRC);
}

/**
 * @brief Pack a set_width_corr_coeff message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param coeff_a Coefficient A
 * @param coeff_b Coefficient B
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_set_width_corr_coeff_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float coeff_a,float coeff_b)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF_LEN];
    _mav_put_float(buf, 0, coeff_a);
    _mav_put_float(buf, 4, coeff_b);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF_LEN);
#else
    mavlink_set_width_corr_coeff_t packet;
    packet.coeff_a = coeff_a;
    packet.coeff_b = coeff_b;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF_MIN_LEN, MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF_LEN, MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF_CRC);
}

/**
 * @brief Encode a set_width_corr_coeff struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param set_width_corr_coeff C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_set_width_corr_coeff_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_set_width_corr_coeff_t* set_width_corr_coeff)
{
    return mavlink_msg_set_width_corr_coeff_pack(system_id, component_id, msg, set_width_corr_coeff->coeff_a, set_width_corr_coeff->coeff_b);
}

/**
 * @brief Encode a set_width_corr_coeff struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param set_width_corr_coeff C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_set_width_corr_coeff_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_set_width_corr_coeff_t* set_width_corr_coeff)
{
    return mavlink_msg_set_width_corr_coeff_pack_chan(system_id, component_id, chan, msg, set_width_corr_coeff->coeff_a, set_width_corr_coeff->coeff_b);
}

/**
 * @brief Send a set_width_corr_coeff message
 * @param chan MAVLink channel to send the message
 *
 * @param coeff_a Coefficient A
 * @param coeff_b Coefficient B
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_set_width_corr_coeff_send(mavlink_channel_t chan, float coeff_a, float coeff_b)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF_LEN];
    _mav_put_float(buf, 0, coeff_a);
    _mav_put_float(buf, 4, coeff_b);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF, buf, MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF_MIN_LEN, MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF_LEN, MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF_CRC);
#else
    mavlink_set_width_corr_coeff_t packet;
    packet.coeff_a = coeff_a;
    packet.coeff_b = coeff_b;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF, (const char *)&packet, MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF_MIN_LEN, MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF_LEN, MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF_CRC);
#endif
}

/**
 * @brief Send a set_width_corr_coeff message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_set_width_corr_coeff_send_struct(mavlink_channel_t chan, const mavlink_set_width_corr_coeff_t* set_width_corr_coeff)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_set_width_corr_coeff_send(chan, set_width_corr_coeff->coeff_a, set_width_corr_coeff->coeff_b);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF, (const char *)set_width_corr_coeff, MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF_MIN_LEN, MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF_LEN, MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF_CRC);
#endif
}

#if MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_set_width_corr_coeff_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float coeff_a, float coeff_b)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, coeff_a);
    _mav_put_float(buf, 4, coeff_b);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF, buf, MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF_MIN_LEN, MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF_LEN, MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF_CRC);
#else
    mavlink_set_width_corr_coeff_t *packet = (mavlink_set_width_corr_coeff_t *)msgbuf;
    packet->coeff_a = coeff_a;
    packet->coeff_b = coeff_b;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF, (const char *)packet, MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF_MIN_LEN, MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF_LEN, MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF_CRC);
#endif
}
#endif

#endif

// MESSAGE SET_WIDTH_CORR_COEFF UNPACKING


/**
 * @brief Get field coeff_a from set_width_corr_coeff message
 *
 * @return Coefficient A
 */
static inline float mavlink_msg_set_width_corr_coeff_get_coeff_a(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field coeff_b from set_width_corr_coeff message
 *
 * @return Coefficient B
 */
static inline float mavlink_msg_set_width_corr_coeff_get_coeff_b(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Decode a set_width_corr_coeff message into a struct
 *
 * @param msg The message to decode
 * @param set_width_corr_coeff C-struct to decode the message contents into
 */
static inline void mavlink_msg_set_width_corr_coeff_decode(const mavlink_message_t* msg, mavlink_set_width_corr_coeff_t* set_width_corr_coeff)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    set_width_corr_coeff->coeff_a = mavlink_msg_set_width_corr_coeff_get_coeff_a(msg);
    set_width_corr_coeff->coeff_b = mavlink_msg_set_width_corr_coeff_get_coeff_b(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF_LEN? msg->len : MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF_LEN;
        memset(set_width_corr_coeff, 0, MAVLINK_MSG_ID_SET_WIDTH_CORR_COEFF_LEN);
    memcpy(set_width_corr_coeff, _MAV_PAYLOAD(msg), len);
#endif
}
