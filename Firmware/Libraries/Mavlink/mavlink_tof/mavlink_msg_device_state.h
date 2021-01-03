#pragma once
// MESSAGE DEVICE_STATE PACKING

#define MAVLINK_MSG_ID_DEVICE_STATE 150

MAVPACKED(
typedef struct __mavlink_device_state_t {
 float apd_voltage_targ; /*< Target APD voltage in volts*/
 float apd_voltage_curr; /*< Current APD voltage in volts*/
 float las_voltage; /*< Laser voltage in volts*/
 float tdc_bin_length; /*< BIN length in mm*/
 int16_t pwm_value; /*< APD dc-dc PWM value, timer ticks*/
 uint16_t voltage_mv; /*< Comparator threshold voltage in mv*/
 uint16_t raw_tof_value; /*< Raw TOF distance value in bins*/
 uint16_t raw_tof_width_value; /*< Raw TOF pulse width value in bins*/
 uint16_t distance; /*< Distance in mm*/
 uint16_t state; /*< Device state*/
 uint8_t pwm_state; /*< 0-manual mode, 1-auto feedback apd voltage mode*/
}) mavlink_device_state_t;

#define MAVLINK_MSG_ID_DEVICE_STATE_LEN 29
#define MAVLINK_MSG_ID_DEVICE_STATE_MIN_LEN 29
#define MAVLINK_MSG_ID_150_LEN 29
#define MAVLINK_MSG_ID_150_MIN_LEN 29

#define MAVLINK_MSG_ID_DEVICE_STATE_CRC 83
#define MAVLINK_MSG_ID_150_CRC 83



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_DEVICE_STATE { \
    150, \
    "DEVICE_STATE", \
    11, \
    {  { "pwm_value", NULL, MAVLINK_TYPE_INT16_T, 0, 16, offsetof(mavlink_device_state_t, pwm_value) }, \
         { "pwm_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 28, offsetof(mavlink_device_state_t, pwm_state) }, \
         { "apd_voltage_targ", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_device_state_t, apd_voltage_targ) }, \
         { "apd_voltage_curr", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_device_state_t, apd_voltage_curr) }, \
         { "las_voltage", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_device_state_t, las_voltage) }, \
         { "voltage_mv", NULL, MAVLINK_TYPE_UINT16_T, 0, 18, offsetof(mavlink_device_state_t, voltage_mv) }, \
         { "raw_tof_value", NULL, MAVLINK_TYPE_UINT16_T, 0, 20, offsetof(mavlink_device_state_t, raw_tof_value) }, \
         { "raw_tof_width_value", NULL, MAVLINK_TYPE_UINT16_T, 0, 22, offsetof(mavlink_device_state_t, raw_tof_width_value) }, \
         { "distance", NULL, MAVLINK_TYPE_UINT16_T, 0, 24, offsetof(mavlink_device_state_t, distance) }, \
         { "state", NULL, MAVLINK_TYPE_UINT16_T, 0, 26, offsetof(mavlink_device_state_t, state) }, \
         { "tdc_bin_length", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_device_state_t, tdc_bin_length) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_DEVICE_STATE { \
    "DEVICE_STATE", \
    11, \
    {  { "pwm_value", NULL, MAVLINK_TYPE_INT16_T, 0, 16, offsetof(mavlink_device_state_t, pwm_value) }, \
         { "pwm_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 28, offsetof(mavlink_device_state_t, pwm_state) }, \
         { "apd_voltage_targ", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_device_state_t, apd_voltage_targ) }, \
         { "apd_voltage_curr", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_device_state_t, apd_voltage_curr) }, \
         { "las_voltage", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_device_state_t, las_voltage) }, \
         { "voltage_mv", NULL, MAVLINK_TYPE_UINT16_T, 0, 18, offsetof(mavlink_device_state_t, voltage_mv) }, \
         { "raw_tof_value", NULL, MAVLINK_TYPE_UINT16_T, 0, 20, offsetof(mavlink_device_state_t, raw_tof_value) }, \
         { "raw_tof_width_value", NULL, MAVLINK_TYPE_UINT16_T, 0, 22, offsetof(mavlink_device_state_t, raw_tof_width_value) }, \
         { "distance", NULL, MAVLINK_TYPE_UINT16_T, 0, 24, offsetof(mavlink_device_state_t, distance) }, \
         { "state", NULL, MAVLINK_TYPE_UINT16_T, 0, 26, offsetof(mavlink_device_state_t, state) }, \
         { "tdc_bin_length", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_device_state_t, tdc_bin_length) }, \
         } \
}
#endif

/**
 * @brief Pack a device_state message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param pwm_value APD dc-dc PWM value, timer ticks
 * @param pwm_state 0-manual mode, 1-auto feedback apd voltage mode
 * @param apd_voltage_targ Target APD voltage in volts
 * @param apd_voltage_curr Current APD voltage in volts
 * @param las_voltage Laser voltage in volts
 * @param voltage_mv Comparator threshold voltage in mv
 * @param raw_tof_value Raw TOF distance value in bins
 * @param raw_tof_width_value Raw TOF pulse width value in bins
 * @param distance Distance in mm
 * @param state Device state
 * @param tdc_bin_length BIN length in mm
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_device_state_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               int16_t pwm_value, uint8_t pwm_state, float apd_voltage_targ, float apd_voltage_curr, float las_voltage, uint16_t voltage_mv, uint16_t raw_tof_value, uint16_t raw_tof_width_value, uint16_t distance, uint16_t state, float tdc_bin_length)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DEVICE_STATE_LEN];
    _mav_put_float(buf, 0, apd_voltage_targ);
    _mav_put_float(buf, 4, apd_voltage_curr);
    _mav_put_float(buf, 8, las_voltage);
    _mav_put_float(buf, 12, tdc_bin_length);
    _mav_put_int16_t(buf, 16, pwm_value);
    _mav_put_uint16_t(buf, 18, voltage_mv);
    _mav_put_uint16_t(buf, 20, raw_tof_value);
    _mav_put_uint16_t(buf, 22, raw_tof_width_value);
    _mav_put_uint16_t(buf, 24, distance);
    _mav_put_uint16_t(buf, 26, state);
    _mav_put_uint8_t(buf, 28, pwm_state);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DEVICE_STATE_LEN);
#else
    mavlink_device_state_t packet;
    packet.apd_voltage_targ = apd_voltage_targ;
    packet.apd_voltage_curr = apd_voltage_curr;
    packet.las_voltage = las_voltage;
    packet.tdc_bin_length = tdc_bin_length;
    packet.pwm_value = pwm_value;
    packet.voltage_mv = voltage_mv;
    packet.raw_tof_value = raw_tof_value;
    packet.raw_tof_width_value = raw_tof_width_value;
    packet.distance = distance;
    packet.state = state;
    packet.pwm_state = pwm_state;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DEVICE_STATE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_DEVICE_STATE;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_DEVICE_STATE_MIN_LEN, MAVLINK_MSG_ID_DEVICE_STATE_LEN, MAVLINK_MSG_ID_DEVICE_STATE_CRC);
}

/**
 * @brief Pack a device_state message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param pwm_value APD dc-dc PWM value, timer ticks
 * @param pwm_state 0-manual mode, 1-auto feedback apd voltage mode
 * @param apd_voltage_targ Target APD voltage in volts
 * @param apd_voltage_curr Current APD voltage in volts
 * @param las_voltage Laser voltage in volts
 * @param voltage_mv Comparator threshold voltage in mv
 * @param raw_tof_value Raw TOF distance value in bins
 * @param raw_tof_width_value Raw TOF pulse width value in bins
 * @param distance Distance in mm
 * @param state Device state
 * @param tdc_bin_length BIN length in mm
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_device_state_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   int16_t pwm_value,uint8_t pwm_state,float apd_voltage_targ,float apd_voltage_curr,float las_voltage,uint16_t voltage_mv,uint16_t raw_tof_value,uint16_t raw_tof_width_value,uint16_t distance,uint16_t state,float tdc_bin_length)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DEVICE_STATE_LEN];
    _mav_put_float(buf, 0, apd_voltage_targ);
    _mav_put_float(buf, 4, apd_voltage_curr);
    _mav_put_float(buf, 8, las_voltage);
    _mav_put_float(buf, 12, tdc_bin_length);
    _mav_put_int16_t(buf, 16, pwm_value);
    _mav_put_uint16_t(buf, 18, voltage_mv);
    _mav_put_uint16_t(buf, 20, raw_tof_value);
    _mav_put_uint16_t(buf, 22, raw_tof_width_value);
    _mav_put_uint16_t(buf, 24, distance);
    _mav_put_uint16_t(buf, 26, state);
    _mav_put_uint8_t(buf, 28, pwm_state);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DEVICE_STATE_LEN);
#else
    mavlink_device_state_t packet;
    packet.apd_voltage_targ = apd_voltage_targ;
    packet.apd_voltage_curr = apd_voltage_curr;
    packet.las_voltage = las_voltage;
    packet.tdc_bin_length = tdc_bin_length;
    packet.pwm_value = pwm_value;
    packet.voltage_mv = voltage_mv;
    packet.raw_tof_value = raw_tof_value;
    packet.raw_tof_width_value = raw_tof_width_value;
    packet.distance = distance;
    packet.state = state;
    packet.pwm_state = pwm_state;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DEVICE_STATE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_DEVICE_STATE;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_DEVICE_STATE_MIN_LEN, MAVLINK_MSG_ID_DEVICE_STATE_LEN, MAVLINK_MSG_ID_DEVICE_STATE_CRC);
}

/**
 * @brief Encode a device_state struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param device_state C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_device_state_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_device_state_t* device_state)
{
    return mavlink_msg_device_state_pack(system_id, component_id, msg, device_state->pwm_value, device_state->pwm_state, device_state->apd_voltage_targ, device_state->apd_voltage_curr, device_state->las_voltage, device_state->voltage_mv, device_state->raw_tof_value, device_state->raw_tof_width_value, device_state->distance, device_state->state, device_state->tdc_bin_length);
}

/**
 * @brief Encode a device_state struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param device_state C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_device_state_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_device_state_t* device_state)
{
    return mavlink_msg_device_state_pack_chan(system_id, component_id, chan, msg, device_state->pwm_value, device_state->pwm_state, device_state->apd_voltage_targ, device_state->apd_voltage_curr, device_state->las_voltage, device_state->voltage_mv, device_state->raw_tof_value, device_state->raw_tof_width_value, device_state->distance, device_state->state, device_state->tdc_bin_length);
}

/**
 * @brief Send a device_state message
 * @param chan MAVLink channel to send the message
 *
 * @param pwm_value APD dc-dc PWM value, timer ticks
 * @param pwm_state 0-manual mode, 1-auto feedback apd voltage mode
 * @param apd_voltage_targ Target APD voltage in volts
 * @param apd_voltage_curr Current APD voltage in volts
 * @param las_voltage Laser voltage in volts
 * @param voltage_mv Comparator threshold voltage in mv
 * @param raw_tof_value Raw TOF distance value in bins
 * @param raw_tof_width_value Raw TOF pulse width value in bins
 * @param distance Distance in mm
 * @param state Device state
 * @param tdc_bin_length BIN length in mm
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_device_state_send(mavlink_channel_t chan, int16_t pwm_value, uint8_t pwm_state, float apd_voltage_targ, float apd_voltage_curr, float las_voltage, uint16_t voltage_mv, uint16_t raw_tof_value, uint16_t raw_tof_width_value, uint16_t distance, uint16_t state, float tdc_bin_length)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DEVICE_STATE_LEN];
    _mav_put_float(buf, 0, apd_voltage_targ);
    _mav_put_float(buf, 4, apd_voltage_curr);
    _mav_put_float(buf, 8, las_voltage);
    _mav_put_float(buf, 12, tdc_bin_length);
    _mav_put_int16_t(buf, 16, pwm_value);
    _mav_put_uint16_t(buf, 18, voltage_mv);
    _mav_put_uint16_t(buf, 20, raw_tof_value);
    _mav_put_uint16_t(buf, 22, raw_tof_width_value);
    _mav_put_uint16_t(buf, 24, distance);
    _mav_put_uint16_t(buf, 26, state);
    _mav_put_uint8_t(buf, 28, pwm_state);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DEVICE_STATE, buf, MAVLINK_MSG_ID_DEVICE_STATE_MIN_LEN, MAVLINK_MSG_ID_DEVICE_STATE_LEN, MAVLINK_MSG_ID_DEVICE_STATE_CRC);
#else
    mavlink_device_state_t packet;
    packet.apd_voltage_targ = apd_voltage_targ;
    packet.apd_voltage_curr = apd_voltage_curr;
    packet.las_voltage = las_voltage;
    packet.tdc_bin_length = tdc_bin_length;
    packet.pwm_value = pwm_value;
    packet.voltage_mv = voltage_mv;
    packet.raw_tof_value = raw_tof_value;
    packet.raw_tof_width_value = raw_tof_width_value;
    packet.distance = distance;
    packet.state = state;
    packet.pwm_state = pwm_state;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DEVICE_STATE, (const char *)&packet, MAVLINK_MSG_ID_DEVICE_STATE_MIN_LEN, MAVLINK_MSG_ID_DEVICE_STATE_LEN, MAVLINK_MSG_ID_DEVICE_STATE_CRC);
#endif
}

/**
 * @brief Send a device_state message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_device_state_send_struct(mavlink_channel_t chan, const mavlink_device_state_t* device_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_device_state_send(chan, device_state->pwm_value, device_state->pwm_state, device_state->apd_voltage_targ, device_state->apd_voltage_curr, device_state->las_voltage, device_state->voltage_mv, device_state->raw_tof_value, device_state->raw_tof_width_value, device_state->distance, device_state->state, device_state->tdc_bin_length);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DEVICE_STATE, (const char *)device_state, MAVLINK_MSG_ID_DEVICE_STATE_MIN_LEN, MAVLINK_MSG_ID_DEVICE_STATE_LEN, MAVLINK_MSG_ID_DEVICE_STATE_CRC);
#endif
}

#if MAVLINK_MSG_ID_DEVICE_STATE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_device_state_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int16_t pwm_value, uint8_t pwm_state, float apd_voltage_targ, float apd_voltage_curr, float las_voltage, uint16_t voltage_mv, uint16_t raw_tof_value, uint16_t raw_tof_width_value, uint16_t distance, uint16_t state, float tdc_bin_length)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, apd_voltage_targ);
    _mav_put_float(buf, 4, apd_voltage_curr);
    _mav_put_float(buf, 8, las_voltage);
    _mav_put_float(buf, 12, tdc_bin_length);
    _mav_put_int16_t(buf, 16, pwm_value);
    _mav_put_uint16_t(buf, 18, voltage_mv);
    _mav_put_uint16_t(buf, 20, raw_tof_value);
    _mav_put_uint16_t(buf, 22, raw_tof_width_value);
    _mav_put_uint16_t(buf, 24, distance);
    _mav_put_uint16_t(buf, 26, state);
    _mav_put_uint8_t(buf, 28, pwm_state);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DEVICE_STATE, buf, MAVLINK_MSG_ID_DEVICE_STATE_MIN_LEN, MAVLINK_MSG_ID_DEVICE_STATE_LEN, MAVLINK_MSG_ID_DEVICE_STATE_CRC);
#else
    mavlink_device_state_t *packet = (mavlink_device_state_t *)msgbuf;
    packet->apd_voltage_targ = apd_voltage_targ;
    packet->apd_voltage_curr = apd_voltage_curr;
    packet->las_voltage = las_voltage;
    packet->tdc_bin_length = tdc_bin_length;
    packet->pwm_value = pwm_value;
    packet->voltage_mv = voltage_mv;
    packet->raw_tof_value = raw_tof_value;
    packet->raw_tof_width_value = raw_tof_width_value;
    packet->distance = distance;
    packet->state = state;
    packet->pwm_state = pwm_state;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DEVICE_STATE, (const char *)packet, MAVLINK_MSG_ID_DEVICE_STATE_MIN_LEN, MAVLINK_MSG_ID_DEVICE_STATE_LEN, MAVLINK_MSG_ID_DEVICE_STATE_CRC);
#endif
}
#endif

#endif

// MESSAGE DEVICE_STATE UNPACKING


/**
 * @brief Get field pwm_value from device_state message
 *
 * @return APD dc-dc PWM value, timer ticks
 */
static inline int16_t mavlink_msg_device_state_get_pwm_value(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  16);
}

/**
 * @brief Get field pwm_state from device_state message
 *
 * @return 0-manual mode, 1-auto feedback apd voltage mode
 */
static inline uint8_t mavlink_msg_device_state_get_pwm_state(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  28);
}

/**
 * @brief Get field apd_voltage_targ from device_state message
 *
 * @return Target APD voltage in volts
 */
static inline float mavlink_msg_device_state_get_apd_voltage_targ(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field apd_voltage_curr from device_state message
 *
 * @return Current APD voltage in volts
 */
static inline float mavlink_msg_device_state_get_apd_voltage_curr(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field las_voltage from device_state message
 *
 * @return Laser voltage in volts
 */
static inline float mavlink_msg_device_state_get_las_voltage(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field voltage_mv from device_state message
 *
 * @return Comparator threshold voltage in mv
 */
static inline uint16_t mavlink_msg_device_state_get_voltage_mv(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  18);
}

/**
 * @brief Get field raw_tof_value from device_state message
 *
 * @return Raw TOF distance value in bins
 */
static inline uint16_t mavlink_msg_device_state_get_raw_tof_value(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  20);
}

/**
 * @brief Get field raw_tof_width_value from device_state message
 *
 * @return Raw TOF pulse width value in bins
 */
static inline uint16_t mavlink_msg_device_state_get_raw_tof_width_value(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  22);
}

/**
 * @brief Get field distance from device_state message
 *
 * @return Distance in mm
 */
static inline uint16_t mavlink_msg_device_state_get_distance(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  24);
}

/**
 * @brief Get field state from device_state message
 *
 * @return Device state
 */
static inline uint16_t mavlink_msg_device_state_get_state(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  26);
}

/**
 * @brief Get field tdc_bin_length from device_state message
 *
 * @return BIN length in mm
 */
static inline float mavlink_msg_device_state_get_tdc_bin_length(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Decode a device_state message into a struct
 *
 * @param msg The message to decode
 * @param device_state C-struct to decode the message contents into
 */
static inline void mavlink_msg_device_state_decode(const mavlink_message_t* msg, mavlink_device_state_t* device_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    device_state->apd_voltage_targ = mavlink_msg_device_state_get_apd_voltage_targ(msg);
    device_state->apd_voltage_curr = mavlink_msg_device_state_get_apd_voltage_curr(msg);
    device_state->las_voltage = mavlink_msg_device_state_get_las_voltage(msg);
    device_state->tdc_bin_length = mavlink_msg_device_state_get_tdc_bin_length(msg);
    device_state->pwm_value = mavlink_msg_device_state_get_pwm_value(msg);
    device_state->voltage_mv = mavlink_msg_device_state_get_voltage_mv(msg);
    device_state->raw_tof_value = mavlink_msg_device_state_get_raw_tof_value(msg);
    device_state->raw_tof_width_value = mavlink_msg_device_state_get_raw_tof_width_value(msg);
    device_state->distance = mavlink_msg_device_state_get_distance(msg);
    device_state->state = mavlink_msg_device_state_get_state(msg);
    device_state->pwm_state = mavlink_msg_device_state_get_pwm_state(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_DEVICE_STATE_LEN? msg->len : MAVLINK_MSG_ID_DEVICE_STATE_LEN;
        memset(device_state, 0, MAVLINK_MSG_ID_DEVICE_STATE_LEN);
    memcpy(device_state, _MAV_PAYLOAD(msg), len);
#endif
}
