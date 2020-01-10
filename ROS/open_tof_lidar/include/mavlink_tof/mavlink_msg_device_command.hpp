// MESSAGE DEVICE_COMMAND support class

#pragma once

namespace mavlink {
namespace mavlink_tof {
namespace msg {

/**
 * @brief DEVICE_COMMAND message
 *
 * Send command to the device
 */
struct DEVICE_COMMAND : mavlink::Message {
    static constexpr msgid_t MSG_ID = 3;
    static constexpr size_t LENGTH = 5;
    static constexpr size_t MIN_LENGTH = 5;
    static constexpr uint8_t CRC_EXTRA = 245;
    static constexpr auto NAME = "DEVICE_COMMAND";


    uint8_t cmd; /*< Command */
    uint32_t value; /*< Additional value */


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
        ss << "  cmd: " << +cmd << std::endl;
        ss << "  value: " << value << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << value;                         // offset: 0
        map << cmd;                           // offset: 4
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> value;                         // offset: 0
        map >> cmd;                           // offset: 4
    }
};

} // namespace msg
} // namespace mavlink_tof
} // namespace mavlink
