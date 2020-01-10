// MESSAGE START_BATCH_MEASUREMENT support class

#pragma once

namespace mavlink {
namespace mavlink_tof {
namespace msg {

/**
 * @brief START_BATCH_MEASUREMENT message
 *
 * Start batch measurement
 */
struct START_BATCH_MEASUREMENT : mavlink::Message {
    static constexpr msgid_t MSG_ID = 103;
    static constexpr size_t LENGTH = 2;
    static constexpr size_t MIN_LENGTH = 2;
    static constexpr uint8_t CRC_EXTRA = 121;
    static constexpr auto NAME = "START_BATCH_MEASUREMENT";


    uint16_t length; /*< Number of measurements */


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
        ss << "  length: " << length << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << length;                        // offset: 0
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> length;                        // offset: 0
    }
};

} // namespace msg
} // namespace mavlink_tof
} // namespace mavlink
