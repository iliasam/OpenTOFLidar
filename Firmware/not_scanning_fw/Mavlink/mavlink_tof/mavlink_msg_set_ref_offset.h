#pragma once
// MESSAGE SET_REF_OFFSET PACKING

#define MAVLINK_MSG_ID_SET_REF_OFFSET 106

MAVPACKED(
typedef struct __mavlink_set_ref_offset_t {
 uint16_t dist_value; /*< Distance to a reference object, mm*/
}) mavlink_set_ref_offset_t;

#define MAVLINK_MSG_ID_SET_REF_OFFSET_LEN 2
#define MAVLINK_MSG_ID_SET_REF_OFFSET_MIN_LEN 2
#define MAVLINK_MSG_ID_106_LEN 2
#define MAVLINK_MSG_ID_106_MIN_LEN 2

#define MAVLINK_MSG_ID_SET_REF_OFFSET_CRC 69
#define MAVLINK_MSG_ID_106_CRC 69



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SET_REF_OFFSET { \
    106, \
    "SET_REF_OFFSET", \
    1, \
    {  { "dist_value", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_set_ref_offset_t, dist_value) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SET_REF_OFFSET { \
    "SET_REF_OFFSET", \
    1, \
    {  { "dist_value", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_set_ref_offset_t, dist_value) }, \
         } \
}
#endif

/**
 * @brief Pack a set_ref_offset message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param dist_value Distance to a reference object, mm
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_set_ref_offset_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint16_t dist_value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SET_REF_OFFSET_LEN];
    _mav_put_uint16_t(buf, 0, dist_value);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SET_REF_OFFSET_LEN);
#else
    mavlink_set_ref_offset_t packet;
    packet.dist_value = dist_value;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SET_REF_OFFSET_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SET_REF_OFFSET;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SET_REF_OFFSET_MIN_LEN, MAVLINK_MSG_ID_SET_REF_OFFSET_LEN, MAVLINK_MSG_ID_SET_REF_OFFSET_CRC);
}

/**
 * @brief Pack a set_ref_offset message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param dist_value Distance to a reference object, mm
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_set_ref_offset_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint16_t dist_value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SET_REF_OFFSET_LEN];
    _mav_put_uint16_t(buf, 0, dist_value);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SET_REF_OFFSET_LEN);
#else
    mavlink_set_ref_offset_t packet;
    packet.dist_value = dist_value;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SET_REF_OFFSET_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SET_REF_OFFSET;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SET_REF_OFFSET_MIN_LEN, MAVLINK_MSG_ID_SET_REF_OFFSET_LEN, MAVLINK_MSG_ID_SET_REF_OFFSET_CRC);
}

/**
 * @brief Encode a set_ref_offset struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param set_ref_offset C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_set_ref_offset_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_set_ref_offset_t* set_ref_offset)
{
    return mavlink_msg_set_ref_offset_pack(system_id, component_id, msg, set_ref_offset->dist_value);
}

/**
 * @brief Encode a set_ref_offset struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param set_ref_offset C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_set_ref_offset_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_set_ref_offset_t* set_ref_offset)
{
    return mavlink_msg_set_ref_offset_pack_chan(system_id, component_id, chan, msg, set_ref_offset->dist_value);
}

/**
 * @brief Send a set_ref_offset message
 * @param chan MAVLink channel to send the message
 *
 * @param dist_value Distance to a reference object, mm
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_set_ref_offset_send(mavlink_channel_t chan, uint16_t dist_value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SET_REF_OFFSET_LEN];
    _mav_put_uint16_t(buf, 0, dist_value);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_REF_OFFSET, buf, MAVLINK_MSG_ID_SET_REF_OFFSET_MIN_LEN, MAVLINK_MSG_ID_SET_REF_OFFSET_LEN, MAVLINK_MSG_ID_SET_REF_OFFSET_CRC);
#else
    mavlink_set_ref_offset_t packet;
    packet.dist_value = dist_value;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_REF_OFFSET, (const char *)&packet, MAVLINK_MSG_ID_SET_REF_OFFSET_MIN_LEN, MAVLINK_MSG_ID_SET_REF_OFFSET_LEN, MAVLINK_MSG_ID_SET_REF_OFFSET_CRC);
#endif
}

/**
 * @brief Send a set_ref_offset message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_set_ref_offset_send_struct(mavlink_channel_t chan, const mavlink_set_ref_offset_t* set_ref_offset)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_set_ref_offset_send(chan, set_ref_offset->dist_value);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_REF_OFFSET, (const char *)set_ref_offset, MAVLINK_MSG_ID_SET_REF_OFFSET_MIN_LEN, MAVLINK_MSG_ID_SET_REF_OFFSET_LEN, MAVLINK_MSG_ID_SET_REF_OFFSET_CRC);
#endif
}

#if MAVLINK_MSG_ID_SET_REF_OFFSET_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_set_ref_offset_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint16_t dist_value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint16_t(buf, 0, dist_value);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_REF_OFFSET, buf, MAVLINK_MSG_ID_SET_REF_OFFSET_MIN_LEN, MAVLINK_MSG_ID_SET_REF_OFFSET_LEN, MAVLINK_MSG_ID_SET_REF_OFFSET_CRC);
#else
    mavlink_set_ref_offset_t *packet = (mavlink_set_ref_offset_t *)msgbuf;
    packet->dist_value = dist_value;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_REF_OFFSET, (const char *)packet, MAVLINK_MSG_ID_SET_REF_OFFSET_MIN_LEN, MAVLINK_MSG_ID_SET_REF_OFFSET_LEN, MAVLINK_MSG_ID_SET_REF_OFFSET_CRC);
#endif
}
#endif

#endif

// MESSAGE SET_REF_OFFSET UNPACKING


/**
 * @brief Get field dist_value from set_ref_offset message
 *
 * @return Distance to a reference object, mm
 */
static inline uint16_t mavlink_msg_set_ref_offset_get_dist_value(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Decode a set_ref_offset message into a struct
 *
 * @param msg The message to decode
 * @param set_ref_offset C-struct to decode the message contents into
 */
static inline void mavlink_msg_set_ref_offset_decode(const mavlink_message_t* msg, mavlink_set_ref_offset_t* set_ref_offset)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    set_ref_offset->dist_value = mavlink_msg_set_ref_offset_get_dist_value(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SET_REF_OFFSET_LEN? msg->len : MAVLINK_MSG_ID_SET_REF_OFFSET_LEN;
        memset(set_ref_offset, 0, MAVLINK_MSG_ID_SET_REF_OFFSET_LEN);
    memcpy(set_ref_offset, _MAV_PAYLOAD(msg), len);
#endif
}
