#pragma once
// MESSAGE SET_APD_VOLTAGE PACKING

#define MAVLINK_MSG_ID_SET_APD_VOLTAGE 100

MAVPACKED(
typedef struct __mavlink_set_apd_voltage_t {
 float voltage; /*< APD voltage in volts. Negative - do nothing*/
 int16_t pwm_value; /*< APD dc-dc PWM value. -1 - do nothing*/
}) mavlink_set_apd_voltage_t;

#define MAVLINK_MSG_ID_SET_APD_VOLTAGE_LEN 6
#define MAVLINK_MSG_ID_SET_APD_VOLTAGE_MIN_LEN 6
#define MAVLINK_MSG_ID_100_LEN 6
#define MAVLINK_MSG_ID_100_MIN_LEN 6

#define MAVLINK_MSG_ID_SET_APD_VOLTAGE_CRC 204
#define MAVLINK_MSG_ID_100_CRC 204



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SET_APD_VOLTAGE { \
    100, \
    "SET_APD_VOLTAGE", \
    2, \
    {  { "pwm_value", NULL, MAVLINK_TYPE_INT16_T, 0, 4, offsetof(mavlink_set_apd_voltage_t, pwm_value) }, \
         { "voltage", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_set_apd_voltage_t, voltage) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SET_APD_VOLTAGE { \
    "SET_APD_VOLTAGE", \
    2, \
    {  { "pwm_value", NULL, MAVLINK_TYPE_INT16_T, 0, 4, offsetof(mavlink_set_apd_voltage_t, pwm_value) }, \
         { "voltage", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_set_apd_voltage_t, voltage) }, \
         } \
}
#endif

/**
 * @brief Pack a set_apd_voltage message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param pwm_value APD dc-dc PWM value. -1 - do nothing
 * @param voltage APD voltage in volts. Negative - do nothing
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_set_apd_voltage_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               int16_t pwm_value, float voltage)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SET_APD_VOLTAGE_LEN];
    _mav_put_float(buf, 0, voltage);
    _mav_put_int16_t(buf, 4, pwm_value);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SET_APD_VOLTAGE_LEN);
#else
    mavlink_set_apd_voltage_t packet;
    packet.voltage = voltage;
    packet.pwm_value = pwm_value;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SET_APD_VOLTAGE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SET_APD_VOLTAGE;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SET_APD_VOLTAGE_MIN_LEN, MAVLINK_MSG_ID_SET_APD_VOLTAGE_LEN, MAVLINK_MSG_ID_SET_APD_VOLTAGE_CRC);
}

/**
 * @brief Pack a set_apd_voltage message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param pwm_value APD dc-dc PWM value. -1 - do nothing
 * @param voltage APD voltage in volts. Negative - do nothing
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_set_apd_voltage_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   int16_t pwm_value,float voltage)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SET_APD_VOLTAGE_LEN];
    _mav_put_float(buf, 0, voltage);
    _mav_put_int16_t(buf, 4, pwm_value);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SET_APD_VOLTAGE_LEN);
#else
    mavlink_set_apd_voltage_t packet;
    packet.voltage = voltage;
    packet.pwm_value = pwm_value;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SET_APD_VOLTAGE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SET_APD_VOLTAGE;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SET_APD_VOLTAGE_MIN_LEN, MAVLINK_MSG_ID_SET_APD_VOLTAGE_LEN, MAVLINK_MSG_ID_SET_APD_VOLTAGE_CRC);
}

/**
 * @brief Encode a set_apd_voltage struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param set_apd_voltage C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_set_apd_voltage_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_set_apd_voltage_t* set_apd_voltage)
{
    return mavlink_msg_set_apd_voltage_pack(system_id, component_id, msg, set_apd_voltage->pwm_value, set_apd_voltage->voltage);
}

/**
 * @brief Encode a set_apd_voltage struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param set_apd_voltage C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_set_apd_voltage_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_set_apd_voltage_t* set_apd_voltage)
{
    return mavlink_msg_set_apd_voltage_pack_chan(system_id, component_id, chan, msg, set_apd_voltage->pwm_value, set_apd_voltage->voltage);
}

/**
 * @brief Send a set_apd_voltage message
 * @param chan MAVLink channel to send the message
 *
 * @param pwm_value APD dc-dc PWM value. -1 - do nothing
 * @param voltage APD voltage in volts. Negative - do nothing
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_set_apd_voltage_send(mavlink_channel_t chan, int16_t pwm_value, float voltage)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SET_APD_VOLTAGE_LEN];
    _mav_put_float(buf, 0, voltage);
    _mav_put_int16_t(buf, 4, pwm_value);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_APD_VOLTAGE, buf, MAVLINK_MSG_ID_SET_APD_VOLTAGE_MIN_LEN, MAVLINK_MSG_ID_SET_APD_VOLTAGE_LEN, MAVLINK_MSG_ID_SET_APD_VOLTAGE_CRC);
#else
    mavlink_set_apd_voltage_t packet;
    packet.voltage = voltage;
    packet.pwm_value = pwm_value;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_APD_VOLTAGE, (const char *)&packet, MAVLINK_MSG_ID_SET_APD_VOLTAGE_MIN_LEN, MAVLINK_MSG_ID_SET_APD_VOLTAGE_LEN, MAVLINK_MSG_ID_SET_APD_VOLTAGE_CRC);
#endif
}

/**
 * @brief Send a set_apd_voltage message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_set_apd_voltage_send_struct(mavlink_channel_t chan, const mavlink_set_apd_voltage_t* set_apd_voltage)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_set_apd_voltage_send(chan, set_apd_voltage->pwm_value, set_apd_voltage->voltage);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_APD_VOLTAGE, (const char *)set_apd_voltage, MAVLINK_MSG_ID_SET_APD_VOLTAGE_MIN_LEN, MAVLINK_MSG_ID_SET_APD_VOLTAGE_LEN, MAVLINK_MSG_ID_SET_APD_VOLTAGE_CRC);
#endif
}

#if MAVLINK_MSG_ID_SET_APD_VOLTAGE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_set_apd_voltage_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int16_t pwm_value, float voltage)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, voltage);
    _mav_put_int16_t(buf, 4, pwm_value);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_APD_VOLTAGE, buf, MAVLINK_MSG_ID_SET_APD_VOLTAGE_MIN_LEN, MAVLINK_MSG_ID_SET_APD_VOLTAGE_LEN, MAVLINK_MSG_ID_SET_APD_VOLTAGE_CRC);
#else
    mavlink_set_apd_voltage_t *packet = (mavlink_set_apd_voltage_t *)msgbuf;
    packet->voltage = voltage;
    packet->pwm_value = pwm_value;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_APD_VOLTAGE, (const char *)packet, MAVLINK_MSG_ID_SET_APD_VOLTAGE_MIN_LEN, MAVLINK_MSG_ID_SET_APD_VOLTAGE_LEN, MAVLINK_MSG_ID_SET_APD_VOLTAGE_CRC);
#endif
}
#endif

#endif

// MESSAGE SET_APD_VOLTAGE UNPACKING


/**
 * @brief Get field pwm_value from set_apd_voltage message
 *
 * @return APD dc-dc PWM value. -1 - do nothing
 */
static inline int16_t mavlink_msg_set_apd_voltage_get_pwm_value(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  4);
}

/**
 * @brief Get field voltage from set_apd_voltage message
 *
 * @return APD voltage in volts. Negative - do nothing
 */
static inline float mavlink_msg_set_apd_voltage_get_voltage(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Decode a set_apd_voltage message into a struct
 *
 * @param msg The message to decode
 * @param set_apd_voltage C-struct to decode the message contents into
 */
static inline void mavlink_msg_set_apd_voltage_decode(const mavlink_message_t* msg, mavlink_set_apd_voltage_t* set_apd_voltage)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    set_apd_voltage->voltage = mavlink_msg_set_apd_voltage_get_voltage(msg);
    set_apd_voltage->pwm_value = mavlink_msg_set_apd_voltage_get_pwm_value(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SET_APD_VOLTAGE_LEN? msg->len : MAVLINK_MSG_ID_SET_APD_VOLTAGE_LEN;
        memset(set_apd_voltage, 0, MAVLINK_MSG_ID_SET_APD_VOLTAGE_LEN);
    memcpy(set_apd_voltage, _MAV_PAYLOAD(msg), len);
#endif
}
