#pragma once
// MESSAGE LONG_PACKET PACKING

#define MAVLINK_MSG_ID_LONG_PACKET 4

MAVPACKED(
typedef struct __mavlink_long_packet_t {
 uint16_t packet_id; /*< Unique code of the big data*/
 uint16_t packet_cnt; /*< Packet counter*/
 uint16_t total_cnt; /*< Total subpackets count*/
 uint8_t data_code; /*< Type of the data*/
 uint8_t payload_size; /*< Size of the data payload*/
 uint8_t data[200]; /*< Data*/
}) mavlink_long_packet_t;

#define MAVLINK_MSG_ID_LONG_PACKET_LEN 208
#define MAVLINK_MSG_ID_LONG_PACKET_MIN_LEN 208
#define MAVLINK_MSG_ID_4_LEN 208
#define MAVLINK_MSG_ID_4_MIN_LEN 208

#define MAVLINK_MSG_ID_LONG_PACKET_CRC 188
#define MAVLINK_MSG_ID_4_CRC 188

#define MAVLINK_MSG_LONG_PACKET_FIELD_DATA_LEN 200

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_LONG_PACKET { \
    4, \
    "LONG_PACKET", \
    6, \
    {  { "data_code", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_long_packet_t, data_code) }, \
         { "packet_id", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_long_packet_t, packet_id) }, \
         { "packet_cnt", NULL, MAVLINK_TYPE_UINT16_T, 0, 2, offsetof(mavlink_long_packet_t, packet_cnt) }, \
         { "total_cnt", NULL, MAVLINK_TYPE_UINT16_T, 0, 4, offsetof(mavlink_long_packet_t, total_cnt) }, \
         { "payload_size", NULL, MAVLINK_TYPE_UINT8_T, 0, 7, offsetof(mavlink_long_packet_t, payload_size) }, \
         { "data", NULL, MAVLINK_TYPE_UINT8_T, 200, 8, offsetof(mavlink_long_packet_t, data) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_LONG_PACKET { \
    "LONG_PACKET", \
    6, \
    {  { "data_code", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_long_packet_t, data_code) }, \
         { "packet_id", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_long_packet_t, packet_id) }, \
         { "packet_cnt", NULL, MAVLINK_TYPE_UINT16_T, 0, 2, offsetof(mavlink_long_packet_t, packet_cnt) }, \
         { "total_cnt", NULL, MAVLINK_TYPE_UINT16_T, 0, 4, offsetof(mavlink_long_packet_t, total_cnt) }, \
         { "payload_size", NULL, MAVLINK_TYPE_UINT8_T, 0, 7, offsetof(mavlink_long_packet_t, payload_size) }, \
         { "data", NULL, MAVLINK_TYPE_UINT8_T, 200, 8, offsetof(mavlink_long_packet_t, data) }, \
         } \
}
#endif

/**
 * @brief Pack a long_packet message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param data_code Type of the data
 * @param packet_id Unique code of the big data
 * @param packet_cnt Packet counter
 * @param total_cnt Total subpackets count
 * @param payload_size Size of the data payload
 * @param data Data
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_long_packet_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t data_code, uint16_t packet_id, uint16_t packet_cnt, uint16_t total_cnt, uint8_t payload_size, const uint8_t *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LONG_PACKET_LEN];
    _mav_put_uint16_t(buf, 0, packet_id);
    _mav_put_uint16_t(buf, 2, packet_cnt);
    _mav_put_uint16_t(buf, 4, total_cnt);
    _mav_put_uint8_t(buf, 6, data_code);
    _mav_put_uint8_t(buf, 7, payload_size);
    _mav_put_uint8_t_array(buf, 8, data, 200);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LONG_PACKET_LEN);
#else
    mavlink_long_packet_t packet;
    packet.packet_id = packet_id;
    packet.packet_cnt = packet_cnt;
    packet.total_cnt = total_cnt;
    packet.data_code = data_code;
    packet.payload_size = payload_size;
    mav_array_memcpy(packet.data, data, sizeof(uint8_t)*200);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LONG_PACKET_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LONG_PACKET;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_LONG_PACKET_MIN_LEN, MAVLINK_MSG_ID_LONG_PACKET_LEN, MAVLINK_MSG_ID_LONG_PACKET_CRC);
}

/**
 * @brief Pack a long_packet message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param data_code Type of the data
 * @param packet_id Unique code of the big data
 * @param packet_cnt Packet counter
 * @param total_cnt Total subpackets count
 * @param payload_size Size of the data payload
 * @param data Data
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_long_packet_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t data_code,uint16_t packet_id,uint16_t packet_cnt,uint16_t total_cnt,uint8_t payload_size,const uint8_t *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LONG_PACKET_LEN];
    _mav_put_uint16_t(buf, 0, packet_id);
    _mav_put_uint16_t(buf, 2, packet_cnt);
    _mav_put_uint16_t(buf, 4, total_cnt);
    _mav_put_uint8_t(buf, 6, data_code);
    _mav_put_uint8_t(buf, 7, payload_size);
    _mav_put_uint8_t_array(buf, 8, data, 200);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LONG_PACKET_LEN);
#else
    mavlink_long_packet_t packet;
    packet.packet_id = packet_id;
    packet.packet_cnt = packet_cnt;
    packet.total_cnt = total_cnt;
    packet.data_code = data_code;
    packet.payload_size = payload_size;
    mav_array_memcpy(packet.data, data, sizeof(uint8_t)*200);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LONG_PACKET_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LONG_PACKET;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_LONG_PACKET_MIN_LEN, MAVLINK_MSG_ID_LONG_PACKET_LEN, MAVLINK_MSG_ID_LONG_PACKET_CRC);
}

/**
 * @brief Encode a long_packet struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param long_packet C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_long_packet_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_long_packet_t* long_packet)
{
    return mavlink_msg_long_packet_pack(system_id, component_id, msg, long_packet->data_code, long_packet->packet_id, long_packet->packet_cnt, long_packet->total_cnt, long_packet->payload_size, long_packet->data);
}

/**
 * @brief Encode a long_packet struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param long_packet C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_long_packet_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_long_packet_t* long_packet)
{
    return mavlink_msg_long_packet_pack_chan(system_id, component_id, chan, msg, long_packet->data_code, long_packet->packet_id, long_packet->packet_cnt, long_packet->total_cnt, long_packet->payload_size, long_packet->data);
}

/**
 * @brief Send a long_packet message
 * @param chan MAVLink channel to send the message
 *
 * @param data_code Type of the data
 * @param packet_id Unique code of the big data
 * @param packet_cnt Packet counter
 * @param total_cnt Total subpackets count
 * @param payload_size Size of the data payload
 * @param data Data
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_long_packet_send(mavlink_channel_t chan, uint8_t data_code, uint16_t packet_id, uint16_t packet_cnt, uint16_t total_cnt, uint8_t payload_size, const uint8_t *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LONG_PACKET_LEN];
    _mav_put_uint16_t(buf, 0, packet_id);
    _mav_put_uint16_t(buf, 2, packet_cnt);
    _mav_put_uint16_t(buf, 4, total_cnt);
    _mav_put_uint8_t(buf, 6, data_code);
    _mav_put_uint8_t(buf, 7, payload_size);
    _mav_put_uint8_t_array(buf, 8, data, 200);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LONG_PACKET, buf, MAVLINK_MSG_ID_LONG_PACKET_MIN_LEN, MAVLINK_MSG_ID_LONG_PACKET_LEN, MAVLINK_MSG_ID_LONG_PACKET_CRC);
#else
    mavlink_long_packet_t packet;
    packet.packet_id = packet_id;
    packet.packet_cnt = packet_cnt;
    packet.total_cnt = total_cnt;
    packet.data_code = data_code;
    packet.payload_size = payload_size;
    mav_array_memcpy(packet.data, data, sizeof(uint8_t)*200);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LONG_PACKET, (const char *)&packet, MAVLINK_MSG_ID_LONG_PACKET_MIN_LEN, MAVLINK_MSG_ID_LONG_PACKET_LEN, MAVLINK_MSG_ID_LONG_PACKET_CRC);
#endif
}

/**
 * @brief Send a long_packet message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_long_packet_send_struct(mavlink_channel_t chan, const mavlink_long_packet_t* long_packet)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_long_packet_send(chan, long_packet->data_code, long_packet->packet_id, long_packet->packet_cnt, long_packet->total_cnt, long_packet->payload_size, long_packet->data);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LONG_PACKET, (const char *)long_packet, MAVLINK_MSG_ID_LONG_PACKET_MIN_LEN, MAVLINK_MSG_ID_LONG_PACKET_LEN, MAVLINK_MSG_ID_LONG_PACKET_CRC);
#endif
}

#if MAVLINK_MSG_ID_LONG_PACKET_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_long_packet_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t data_code, uint16_t packet_id, uint16_t packet_cnt, uint16_t total_cnt, uint8_t payload_size, const uint8_t *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint16_t(buf, 0, packet_id);
    _mav_put_uint16_t(buf, 2, packet_cnt);
    _mav_put_uint16_t(buf, 4, total_cnt);
    _mav_put_uint8_t(buf, 6, data_code);
    _mav_put_uint8_t(buf, 7, payload_size);
    _mav_put_uint8_t_array(buf, 8, data, 200);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LONG_PACKET, buf, MAVLINK_MSG_ID_LONG_PACKET_MIN_LEN, MAVLINK_MSG_ID_LONG_PACKET_LEN, MAVLINK_MSG_ID_LONG_PACKET_CRC);
#else
    mavlink_long_packet_t *packet = (mavlink_long_packet_t *)msgbuf;
    packet->packet_id = packet_id;
    packet->packet_cnt = packet_cnt;
    packet->total_cnt = total_cnt;
    packet->data_code = data_code;
    packet->payload_size = payload_size;
    mav_array_memcpy(packet->data, data, sizeof(uint8_t)*200);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LONG_PACKET, (const char *)packet, MAVLINK_MSG_ID_LONG_PACKET_MIN_LEN, MAVLINK_MSG_ID_LONG_PACKET_LEN, MAVLINK_MSG_ID_LONG_PACKET_CRC);
#endif
}
#endif

#endif

// MESSAGE LONG_PACKET UNPACKING


/**
 * @brief Get field data_code from long_packet message
 *
 * @return Type of the data
 */
static inline uint8_t mavlink_msg_long_packet_get_data_code(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  6);
}

/**
 * @brief Get field packet_id from long_packet message
 *
 * @return Unique code of the big data
 */
static inline uint16_t mavlink_msg_long_packet_get_packet_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Get field packet_cnt from long_packet message
 *
 * @return Packet counter
 */
static inline uint16_t mavlink_msg_long_packet_get_packet_cnt(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  2);
}

/**
 * @brief Get field total_cnt from long_packet message
 *
 * @return Total subpackets count
 */
static inline uint16_t mavlink_msg_long_packet_get_total_cnt(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  4);
}

/**
 * @brief Get field payload_size from long_packet message
 *
 * @return Size of the data payload
 */
static inline uint8_t mavlink_msg_long_packet_get_payload_size(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  7);
}

/**
 * @brief Get field data from long_packet message
 *
 * @return Data
 */
static inline uint16_t mavlink_msg_long_packet_get_data(const mavlink_message_t* msg, uint8_t *data)
{
    return _MAV_RETURN_uint8_t_array(msg, data, 200,  8);
}

/**
 * @brief Decode a long_packet message into a struct
 *
 * @param msg The message to decode
 * @param long_packet C-struct to decode the message contents into
 */
static inline void mavlink_msg_long_packet_decode(const mavlink_message_t* msg, mavlink_long_packet_t* long_packet)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    long_packet->packet_id = mavlink_msg_long_packet_get_packet_id(msg);
    long_packet->packet_cnt = mavlink_msg_long_packet_get_packet_cnt(msg);
    long_packet->total_cnt = mavlink_msg_long_packet_get_total_cnt(msg);
    long_packet->data_code = mavlink_msg_long_packet_get_data_code(msg);
    long_packet->payload_size = mavlink_msg_long_packet_get_payload_size(msg);
    mavlink_msg_long_packet_get_data(msg, long_packet->data);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_LONG_PACKET_LEN? msg->len : MAVLINK_MSG_ID_LONG_PACKET_LEN;
        memset(long_packet, 0, MAVLINK_MSG_ID_LONG_PACKET_LEN);
    memcpy(long_packet, _MAV_PAYLOAD(msg), len);
#endif
}
