#pragma once
// MESSAGE MOTOR_STATE PACKING

#define MAVLINK_MSG_ID_MOTOR_STATE 151

MAVPACKED(
typedef struct __mavlink_motor_state_t {
 float motor_speed; /*< Current speed value, rotations per second*/
 float setted_motor_speed; /*< Manual setted auto speed value, rotations per second*/
 uint16_t pwm_duty; /*< Current PWM value, timer ticks*/
 uint16_t setted_pwm_duty; /*< Manual setted PWM value/min PWM value, timer ticks*/
 uint16_t state; /*< Device state*/
}) mavlink_motor_state_t;

#define MAVLINK_MSG_ID_MOTOR_STATE_LEN 14
#define MAVLINK_MSG_ID_MOTOR_STATE_MIN_LEN 14
#define MAVLINK_MSG_ID_151_LEN 14
#define MAVLINK_MSG_ID_151_MIN_LEN 14

#define MAVLINK_MSG_ID_MOTOR_STATE_CRC 162
#define MAVLINK_MSG_ID_151_CRC 162



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MOTOR_STATE { \
    151, \
    "MOTOR_STATE", \
    5, \
    {  { "pwm_duty", NULL, MAVLINK_TYPE_UINT16_T, 0, 8, offsetof(mavlink_motor_state_t, pwm_duty) }, \
         { "motor_speed", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_motor_state_t, motor_speed) }, \
         { "setted_pwm_duty", NULL, MAVLINK_TYPE_UINT16_T, 0, 10, offsetof(mavlink_motor_state_t, setted_pwm_duty) }, \
         { "setted_motor_speed", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_motor_state_t, setted_motor_speed) }, \
         { "state", NULL, MAVLINK_TYPE_UINT16_T, 0, 12, offsetof(mavlink_motor_state_t, state) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MOTOR_STATE { \
    "MOTOR_STATE", \
    5, \
    {  { "pwm_duty", NULL, MAVLINK_TYPE_UINT16_T, 0, 8, offsetof(mavlink_motor_state_t, pwm_duty) }, \
         { "motor_speed", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_motor_state_t, motor_speed) }, \
         { "setted_pwm_duty", NULL, MAVLINK_TYPE_UINT16_T, 0, 10, offsetof(mavlink_motor_state_t, setted_pwm_duty) }, \
         { "setted_motor_speed", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_motor_state_t, setted_motor_speed) }, \
         { "state", NULL, MAVLINK_TYPE_UINT16_T, 0, 12, offsetof(mavlink_motor_state_t, state) }, \
         } \
}
#endif

/**
 * @brief Pack a motor_state message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param pwm_duty Current PWM value, timer ticks
 * @param motor_speed Current speed value, rotations per second
 * @param setted_pwm_duty Manual setted PWM value/min PWM value, timer ticks
 * @param setted_motor_speed Manual setted auto speed value, rotations per second
 * @param state Device state
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motor_state_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint16_t pwm_duty, float motor_speed, uint16_t setted_pwm_duty, float setted_motor_speed, uint16_t state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MOTOR_STATE_LEN];
    _mav_put_float(buf, 0, motor_speed);
    _mav_put_float(buf, 4, setted_motor_speed);
    _mav_put_uint16_t(buf, 8, pwm_duty);
    _mav_put_uint16_t(buf, 10, setted_pwm_duty);
    _mav_put_uint16_t(buf, 12, state);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MOTOR_STATE_LEN);
#else
    mavlink_motor_state_t packet;
    packet.motor_speed = motor_speed;
    packet.setted_motor_speed = setted_motor_speed;
    packet.pwm_duty = pwm_duty;
    packet.setted_pwm_duty = setted_pwm_duty;
    packet.state = state;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MOTOR_STATE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MOTOR_STATE;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MOTOR_STATE_MIN_LEN, MAVLINK_MSG_ID_MOTOR_STATE_LEN, MAVLINK_MSG_ID_MOTOR_STATE_CRC);
}

/**
 * @brief Pack a motor_state message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param pwm_duty Current PWM value, timer ticks
 * @param motor_speed Current speed value, rotations per second
 * @param setted_pwm_duty Manual setted PWM value/min PWM value, timer ticks
 * @param setted_motor_speed Manual setted auto speed value, rotations per second
 * @param state Device state
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motor_state_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint16_t pwm_duty,float motor_speed,uint16_t setted_pwm_duty,float setted_motor_speed,uint16_t state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MOTOR_STATE_LEN];
    _mav_put_float(buf, 0, motor_speed);
    _mav_put_float(buf, 4, setted_motor_speed);
    _mav_put_uint16_t(buf, 8, pwm_duty);
    _mav_put_uint16_t(buf, 10, setted_pwm_duty);
    _mav_put_uint16_t(buf, 12, state);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MOTOR_STATE_LEN);
#else
    mavlink_motor_state_t packet;
    packet.motor_speed = motor_speed;
    packet.setted_motor_speed = setted_motor_speed;
    packet.pwm_duty = pwm_duty;
    packet.setted_pwm_duty = setted_pwm_duty;
    packet.state = state;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MOTOR_STATE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MOTOR_STATE;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MOTOR_STATE_MIN_LEN, MAVLINK_MSG_ID_MOTOR_STATE_LEN, MAVLINK_MSG_ID_MOTOR_STATE_CRC);
}

/**
 * @brief Encode a motor_state struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param motor_state C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motor_state_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_motor_state_t* motor_state)
{
    return mavlink_msg_motor_state_pack(system_id, component_id, msg, motor_state->pwm_duty, motor_state->motor_speed, motor_state->setted_pwm_duty, motor_state->setted_motor_speed, motor_state->state);
}

/**
 * @brief Encode a motor_state struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param motor_state C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motor_state_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_motor_state_t* motor_state)
{
    return mavlink_msg_motor_state_pack_chan(system_id, component_id, chan, msg, motor_state->pwm_duty, motor_state->motor_speed, motor_state->setted_pwm_duty, motor_state->setted_motor_speed, motor_state->state);
}

/**
 * @brief Send a motor_state message
 * @param chan MAVLink channel to send the message
 *
 * @param pwm_duty Current PWM value, timer ticks
 * @param motor_speed Current speed value, rotations per second
 * @param setted_pwm_duty Manual setted PWM value/min PWM value, timer ticks
 * @param setted_motor_speed Manual setted auto speed value, rotations per second
 * @param state Device state
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_motor_state_send(mavlink_channel_t chan, uint16_t pwm_duty, float motor_speed, uint16_t setted_pwm_duty, float setted_motor_speed, uint16_t state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MOTOR_STATE_LEN];
    _mav_put_float(buf, 0, motor_speed);
    _mav_put_float(buf, 4, setted_motor_speed);
    _mav_put_uint16_t(buf, 8, pwm_duty);
    _mav_put_uint16_t(buf, 10, setted_pwm_duty);
    _mav_put_uint16_t(buf, 12, state);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_STATE, buf, MAVLINK_MSG_ID_MOTOR_STATE_MIN_LEN, MAVLINK_MSG_ID_MOTOR_STATE_LEN, MAVLINK_MSG_ID_MOTOR_STATE_CRC);
#else
    mavlink_motor_state_t packet;
    packet.motor_speed = motor_speed;
    packet.setted_motor_speed = setted_motor_speed;
    packet.pwm_duty = pwm_duty;
    packet.setted_pwm_duty = setted_pwm_duty;
    packet.state = state;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_STATE, (const char *)&packet, MAVLINK_MSG_ID_MOTOR_STATE_MIN_LEN, MAVLINK_MSG_ID_MOTOR_STATE_LEN, MAVLINK_MSG_ID_MOTOR_STATE_CRC);
#endif
}

/**
 * @brief Send a motor_state message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_motor_state_send_struct(mavlink_channel_t chan, const mavlink_motor_state_t* motor_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_motor_state_send(chan, motor_state->pwm_duty, motor_state->motor_speed, motor_state->setted_pwm_duty, motor_state->setted_motor_speed, motor_state->state);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_STATE, (const char *)motor_state, MAVLINK_MSG_ID_MOTOR_STATE_MIN_LEN, MAVLINK_MSG_ID_MOTOR_STATE_LEN, MAVLINK_MSG_ID_MOTOR_STATE_CRC);
#endif
}

#if MAVLINK_MSG_ID_MOTOR_STATE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_motor_state_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint16_t pwm_duty, float motor_speed, uint16_t setted_pwm_duty, float setted_motor_speed, uint16_t state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, motor_speed);
    _mav_put_float(buf, 4, setted_motor_speed);
    _mav_put_uint16_t(buf, 8, pwm_duty);
    _mav_put_uint16_t(buf, 10, setted_pwm_duty);
    _mav_put_uint16_t(buf, 12, state);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_STATE, buf, MAVLINK_MSG_ID_MOTOR_STATE_MIN_LEN, MAVLINK_MSG_ID_MOTOR_STATE_LEN, MAVLINK_MSG_ID_MOTOR_STATE_CRC);
#else
    mavlink_motor_state_t *packet = (mavlink_motor_state_t *)msgbuf;
    packet->motor_speed = motor_speed;
    packet->setted_motor_speed = setted_motor_speed;
    packet->pwm_duty = pwm_duty;
    packet->setted_pwm_duty = setted_pwm_duty;
    packet->state = state;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_STATE, (const char *)packet, MAVLINK_MSG_ID_MOTOR_STATE_MIN_LEN, MAVLINK_MSG_ID_MOTOR_STATE_LEN, MAVLINK_MSG_ID_MOTOR_STATE_CRC);
#endif
}
#endif

#endif

// MESSAGE MOTOR_STATE UNPACKING


/**
 * @brief Get field pwm_duty from motor_state message
 *
 * @return Current PWM value, timer ticks
 */
static inline uint16_t mavlink_msg_motor_state_get_pwm_duty(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  8);
}

/**
 * @brief Get field motor_speed from motor_state message
 *
 * @return Current speed value, rotations per second
 */
static inline float mavlink_msg_motor_state_get_motor_speed(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field setted_pwm_duty from motor_state message
 *
 * @return Manual setted PWM value/min PWM value, timer ticks
 */
static inline uint16_t mavlink_msg_motor_state_get_setted_pwm_duty(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  10);
}

/**
 * @brief Get field setted_motor_speed from motor_state message
 *
 * @return Manual setted auto speed value, rotations per second
 */
static inline float mavlink_msg_motor_state_get_setted_motor_speed(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field state from motor_state message
 *
 * @return Device state
 */
static inline uint16_t mavlink_msg_motor_state_get_state(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  12);
}

/**
 * @brief Decode a motor_state message into a struct
 *
 * @param msg The message to decode
 * @param motor_state C-struct to decode the message contents into
 */
static inline void mavlink_msg_motor_state_decode(const mavlink_message_t* msg, mavlink_motor_state_t* motor_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    motor_state->motor_speed = mavlink_msg_motor_state_get_motor_speed(msg);
    motor_state->setted_motor_speed = mavlink_msg_motor_state_get_setted_motor_speed(msg);
    motor_state->pwm_duty = mavlink_msg_motor_state_get_pwm_duty(msg);
    motor_state->setted_pwm_duty = mavlink_msg_motor_state_get_setted_pwm_duty(msg);
    motor_state->state = mavlink_msg_motor_state_get_state(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MOTOR_STATE_LEN? msg->len : MAVLINK_MSG_ID_MOTOR_STATE_LEN;
        memset(motor_state, 0, MAVLINK_MSG_ID_MOTOR_STATE_LEN);
    memcpy(motor_state, _MAV_PAYLOAD(msg), len);
#endif
}
