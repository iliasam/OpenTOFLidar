// MESSAGE SET_MOTOR_DUTY support class

#pragma once

namespace mavlink {
namespace mavlink_tof {
namespace msg {

/**
 * @brief SET_MOTOR_DUTY message
 *
 * Set motor PWM duty and switch to manual mode
 */
struct SET_MOTOR_DUTY : mavlink::Message {
    static constexpr msgid_t MSG_ID = 110;
    static constexpr size_t LENGTH = 2;
    static constexpr size_t MIN_LENGTH = 2;
    static constexpr uint8_t CRC_EXTRA = 216;
    static constexpr auto NAME = "SET_MOTOR_DUTY";


    uint16_t duty; /*< PWM duty, timer ticks */


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
        ss << "  duty: " << duty << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << duty;                          // offset: 0
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> duty;                          // offset: 0
    }
};

} // namespace msg
} // namespace mavlink_tof
} // namespace mavlink
