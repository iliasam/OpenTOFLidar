// MESSAGE SET_REF_OFFSET support class

#pragma once

namespace mavlink {
namespace mavlink_tof {
namespace msg {

/**
 * @brief SET_REF_OFFSET message
 *
 * Set reference offset
 */
struct SET_REF_OFFSET : mavlink::Message {
    static constexpr msgid_t MSG_ID = 106;
    static constexpr size_t LENGTH = 2;
    static constexpr size_t MIN_LENGTH = 2;
    static constexpr uint8_t CRC_EXTRA = 69;
    static constexpr auto NAME = "SET_REF_OFFSET";


    uint16_t dist_value; /*< Distance to a reference object, mm */


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
        ss << "  dist_value: " << dist_value << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << dist_value;                    // offset: 0
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> dist_value;                    // offset: 0
    }
};

} // namespace msg
} // namespace mavlink_tof
} // namespace mavlink
