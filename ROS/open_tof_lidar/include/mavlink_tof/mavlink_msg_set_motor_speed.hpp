// MESSAGE SET_MOTOR_SPEED support class

#pragma once

namespace mavlink {
namespace mavlink_tof {
namespace msg {

/**
 * @brief SET_MOTOR_SPEED message
 *
 * Set motor speed and switch to auto mode
 */
struct SET_MOTOR_SPEED : mavlink::Message {
    static constexpr msgid_t MSG_ID = 111;
    static constexpr size_t LENGTH = 4;
    static constexpr size_t MIN_LENGTH = 4;
    static constexpr uint8_t CRC_EXTRA = 146;
    static constexpr auto NAME = "SET_MOTOR_SPEED";


    float speed; /*< Rotations per second */


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
        ss << "  speed: " << speed << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << speed;                         // offset: 0
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> speed;                         // offset: 0
    }
};

} // namespace msg
} // namespace mavlink_tof
} // namespace mavlink
