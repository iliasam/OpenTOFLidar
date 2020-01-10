// MESSAGE MOTOR_STATE support class

#pragma once

namespace mavlink {
namespace mavlink_tof {
namespace msg {

/**
 * @brief MOTOR_STATE message
 *
 * Message with motor info
 */
struct MOTOR_STATE : mavlink::Message {
    static constexpr msgid_t MSG_ID = 151;
    static constexpr size_t LENGTH = 14;
    static constexpr size_t MIN_LENGTH = 14;
    static constexpr uint8_t CRC_EXTRA = 162;
    static constexpr auto NAME = "MOTOR_STATE";


    uint16_t pwm_duty; /*< Current PWM value, timer ticks */
    float motor_speed; /*< Current speed value, rotations per second */
    uint16_t setted_pwm_duty; /*< Manual setted PWM value/min PWM value, timer ticks */
    float setted_motor_speed; /*< Manual setted auto speed value, rotations per second */
    uint16_t state; /*< Device state */


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
        ss << "  pwm_duty: " << pwm_duty << std::endl;
        ss << "  motor_speed: " << motor_speed << std::endl;
        ss << "  setted_pwm_duty: " << setted_pwm_duty << std::endl;
        ss << "  setted_motor_speed: " << setted_motor_speed << std::endl;
        ss << "  state: " << state << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << motor_speed;                   // offset: 0
        map << setted_motor_speed;            // offset: 4
        map << pwm_duty;                      // offset: 8
        map << setted_pwm_duty;               // offset: 10
        map << state;                         // offset: 12
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> motor_speed;                   // offset: 0
        map >> setted_motor_speed;            // offset: 4
        map >> pwm_duty;                      // offset: 8
        map >> setted_pwm_duty;               // offset: 10
        map >> state;                         // offset: 12
    }
};

} // namespace msg
} // namespace mavlink_tof
} // namespace mavlink
