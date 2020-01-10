// MESSAGE SET_COMP_THRESHOLD support class

#pragma once

namespace mavlink {
namespace mavlink_tof {
namespace msg {

/**
 * @brief SET_COMP_THRESHOLD message
 *
 * Set comparator threshold voltage
 */
struct SET_COMP_THRESHOLD : mavlink::Message {
    static constexpr msgid_t MSG_ID = 102;
    static constexpr size_t LENGTH = 2;
    static constexpr size_t MIN_LENGTH = 2;
    static constexpr uint8_t CRC_EXTRA = 77;
    static constexpr auto NAME = "SET_COMP_THRESHOLD";


    uint16_t voltage_mv; /*< Comparator threshold voltage in mv */


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
        ss << "  voltage_mv: " << voltage_mv << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << voltage_mv;                    // offset: 0
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> voltage_mv;                    // offset: 0
    }
};

} // namespace msg
} // namespace mavlink_tof
} // namespace mavlink
