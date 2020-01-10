// MESSAGE LONG_PACKET support class

#pragma once

namespace mavlink {
namespace mavlink_tof {
namespace msg {

/**
 * @brief LONG_PACKET message
 *
 * Packet of the long data
 */
struct LONG_PACKET : mavlink::Message {
    static constexpr msgid_t MSG_ID = 4;
    static constexpr size_t LENGTH = 208;
    static constexpr size_t MIN_LENGTH = 208;
    static constexpr uint8_t CRC_EXTRA = 188;
    static constexpr auto NAME = "LONG_PACKET";


    uint8_t data_code; /*< Type of the data */
    uint16_t packet_id; /*< Unique code of the big data */
    uint16_t packet_cnt; /*< Packet counter */
    uint16_t total_cnt; /*< Total subpackets count */
    uint8_t payload_size; /*< Size of the data payload */
    std::array<uint8_t, 200> data; /*< Data */


    inline std::string get_name(void) const override
    {
            return NAME;
    }

    inline Info get_message_info(void) const override
    {
            return { MSG_ID, LENGTH, MIN_LENGTH, CRC_EXTRA };
    }

    inline std::string to_yaml(void) const override
    {
        std::stringstream ss;

        ss << NAME << ":" << std::endl;
        ss << "  data_code: " << +data_code << std::endl;
        ss << "  packet_id: " << packet_id << std::endl;
        ss << "  packet_cnt: " << packet_cnt << std::endl;
        ss << "  total_cnt: " << total_cnt << std::endl;
        ss << "  payload_size: " << +payload_size << std::endl;
        ss << "  data: [" << to_string(data) << "]" << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << packet_id;                     // offset: 0
        map << packet_cnt;                    // offset: 2
        map << total_cnt;                     // offset: 4
        map << data_code;                     // offset: 6
        map << payload_size;                  // offset: 7
        map << data;                          // offset: 8
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> packet_id;                     // offset: 0
        map >> packet_cnt;                    // offset: 2
        map >> total_cnt;                     // offset: 4
        map >> data_code;                     // offset: 6
        map >> payload_size;                  // offset: 7
        map >> data;                          // offset: 8
    }
};

} // namespace msg
} // namespace mavlink_tof
} // namespace mavlink
