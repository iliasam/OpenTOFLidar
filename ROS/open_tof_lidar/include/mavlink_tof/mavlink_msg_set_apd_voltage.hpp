// MESSAGE SET_APD_VOLTAGE support class

#pragma once

namespace mavlink {
namespace mavlink_tof {
namespace msg {

/**
 * @brief SET_APD_VOLTAGE message
 *
 * Set APD voltage
 */
struct SET_APD_VOLTAGE : mavlink::Message {
    static constexpr msgid_t MSG_ID = 100;
    static constexpr size_t LENGTH = 6;
    static constexpr size_t MIN_LENGTH = 6;
    static constexpr uint8_t CRC_EXTRA = 204;
    static constexpr auto NAME = "SET_APD_VOLTAGE";


    int16_t pwm_value; /*< APD dc-dc PWM value. -1 - do nothing */
    float voltage; /*< APD voltage in volts. Negative - do nothing */


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
        ss << "  pwm_value: " << pwm_value << std::endl;
        ss << "  voltage: " << voltage << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << voltage;                       // offset: 0
        map << pwm_value;                     // offset: 4
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> voltage;                       // offset: 0
        map >> pwm_value;                     // offset: 4
    }
};

} // namespace msg
} // namespace mavlink_tof
} // namespace mavlink
