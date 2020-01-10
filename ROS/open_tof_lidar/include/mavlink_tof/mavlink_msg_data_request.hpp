// MESSAGE DATA_REQUEST support class

#pragma once

namespace mavlink {
namespace mavlink_tof {
namespace msg {

/**
 * @brief DATA_REQUEST message
 *
 * Request for data
 */
struct DATA_REQUEST : mavlink::Message {
    static constexpr msgid_t MSG_ID = 2;
    static constexpr size_t LENGTH = 1;
    static constexpr size_t MIN_LENGTH = 1;
    static constexpr uint8_t CRC_EXTRA = 157;
    static constexpr auto NAME = "DATA_REQUEST";


    uint8_t data_type; /*< Type of the needed data */


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
        ss << "  data_type: " << +data_type << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << data_type;                     // offset: 0
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> data_type;                     // offset: 0
    }
};

} // namespace msg
} // namespace mavlink_tof
} // namespace mavlink
