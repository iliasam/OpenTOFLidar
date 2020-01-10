#pragma once
// MESSAGE SET_MOTOR_DUTY PACKING

#define MAVLINK_MSG_ID_SET_MOTOR_DUTY 110

MAVPACKED(
typedef struct __mavlink_set_motor_duty_t {
 uint16_t duty; /*< PWM duty, timer ticks*/
}) mavlink_set_motor_duty_t;

#define MAVLINK_MSG_ID_SET_MOTOR_DUTY_LEN 2
#define MAVLINK_MSG_ID_SET_MOTOR_DUTY_MIN_LEN 2
#define MAVLINK_MSG_ID_110_LEN 2
#define MAVLINK_MSG_ID_110_MIN_LEN 2

#define MAVLINK_MSG_ID_SET_MOTOR_DUTY_CRC 216
#define MAVLINK_MSG_ID_110_CRC 216



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SET_MOTOR_DUTY { \
    110, \
    "SET_MOTOR_DUTY", \
    1, \
    {  { "duty", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_set_motor_duty_t, duty) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SET_MOTOR_DUTY { \
    "SET_MOTOR_DUTY", \
    1, \
    {  { "duty", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_set_motor_duty_t, duty) }, \
         } \
}
#endif

/**
 * @brief Pack a set_motor_duty message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param duty PWM duty, timer ticks
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_set_motor_duty_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint16_t duty)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SET_MOTOR_DUTY_LEN];
    _mav_put_uint16_t(buf, 0, duty);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SET_MOTOR_DUTY_LEN);
#else
    mavlink_set_motor_duty_t packet;
    packet.duty = duty;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SET_MOTOR_DUTY_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SET_MOTOR_DUTY;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SET_MOTOR_DUTY_MIN_LEN, MAVLINK_MSG_ID_SET_MOTOR_DUTY_LEN, MAVLINK_MSG_ID_SET_MOTOR_DUTY_CRC);
}

/**
 * @brief Pack a set_motor_duty message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param duty PWM duty, timer ticks
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_set_motor_duty_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint16_t duty)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SET_MOTOR_DUTY_LEN];
    _mav_put_uint16_t(buf, 0, duty);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SET_MOTOR_DUTY_LEN);
#else
    mavlink_set_motor_duty_t packet;
    packet.duty = duty;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SET_MOTOR_DUTY_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SET_MOTOR_DUTY;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SET_MOTOR_DUTY_MIN_LEN, MAVLINK_MSG_ID_SET_MOTOR_DUTY_LEN, MAVLINK_MSG_ID_SET_MOTOR_DUTY_CRC);
}

/**
 * @brief Encode a set_motor_duty struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param set_motor_duty C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_set_motor_duty_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_set_motor_duty_t* set_motor_duty)
{
    return mavlink_msg_set_motor_duty_pack(system_id, component_id, msg, set_motor_duty->duty);
}

/**
 * @brief Encode a set_motor_duty struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param set_motor_duty C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_set_motor_duty_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_set_motor_duty_t* set_motor_duty)
{
    return mavlink_msg_set_motor_duty_pack_chan(system_id, component_id, chan, msg, set_motor_duty->duty);
}

/**
 * @brief Send a set_motor_duty message
 * @param chan MAVLink channel to send the message
 *
 * @param duty PWM duty, timer ticks
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_set_motor_duty_send(mavlink_channel_t chan, uint16_t duty)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SET_MOTOR_DUTY_LEN];
    _mav_put_uint16_t(buf, 0, duty);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_MOTOR_DUTY, buf, MAVLINK_MSG_ID_SET_MOTOR_DUTY_MIN_LEN, MAVLINK_MSG_ID_SET_MOTOR_DUTY_LEN, MAVLINK_MSG_ID_SET_MOTOR_DUTY_CRC);
#else
    mavlink_set_motor_duty_t packet;
    packet.duty = duty;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_MOTOR_DUTY, (const char *)&packet, MAVLINK_MSG_ID_SET_MOTOR_DUTY_MIN_LEN, MAVLINK_MSG_ID_SET_MOTOR_DUTY_LEN, MAVLINK_MSG_ID_SET_MOTOR_DUTY_CRC);
#endif
}

/**
 * @brief Send a set_motor_duty message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_set_motor_duty_send_struct(mavlink_channel_t chan, const mavlink_set_motor_duty_t* set_motor_duty)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_set_motor_duty_send(chan, set_motor_duty->duty);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_MOTOR_DUTY, (const char *)set_motor_duty, MAVLINK_MSG_ID_SET_MOTOR_DUTY_MIN_LEN, MAVLINK_MSG_ID_SET_MOTOR_DUTY_LEN, MAVLINK_MSG_ID_SET_MOTOR_DUTY_CRC);
#endif
}

#if MAVLINK_MSG_ID_SET_MOTOR_DUTY_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_set_motor_duty_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint16_t duty)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint16_t(buf, 0, duty);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_MOTOR_DUTY, buf, MAVLINK_MSG_ID_SET_MOTOR_DUTY_MIN_LEN, MAVLINK_MSG_ID_SET_MOTOR_DUTY_LEN, MAVLINK_MSG_ID_SET_MOTOR_DUTY_CRC);
#else
    mavlink_set_motor_duty_t *packet = (mavlink_set_motor_duty_t *)msgbuf;
    packet->duty = duty;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_MOTOR_DUTY, (const char *)packet, MAVLINK_MSG_ID_SET_MOTOR_DUTY_MIN_LEN, MAVLINK_MSG_ID_SET_MOTOR_DUTY_LEN, MAVLINK_MSG_ID_SET_MOTOR_DUTY_CRC);
#endif
}
#endif

#endif

// MESSAGE SET_MOTOR_DUTY UNPACKING


/**
 * @brief Get field duty from set_motor_duty message
 *
 * @return PWM duty, timer ticks
 */
static inline uint16_t mavlink_msg_set_motor_duty_get_duty(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Decode a set_motor_duty message into a struct
 *
 * @param msg The message to decode
 * @param set_motor_duty C-struct to decode the message contents into
 */
static inline void mavlink_msg_set_motor_duty_decode(const mavlink_message_t* msg, mavlink_set_motor_duty_t* set_motor_duty)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    set_motor_duty->duty = mavlink_msg_set_motor_duty_get_duty(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SET_MOTOR_DUTY_LEN? msg->len : MAVLINK_MSG_ID_SET_MOTOR_DUTY_LEN;
        memset(set_motor_duty, 0, MAVLINK_MSG_ID_SET_MOTOR_DUTY_LEN);
    memcpy(set_motor_duty, _MAV_PAYLOAD(msg), len);
#endif
}
