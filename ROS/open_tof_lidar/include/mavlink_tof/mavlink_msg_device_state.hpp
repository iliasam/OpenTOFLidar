// MESSAGE DEVICE_STATE support class

#pragma once

namespace mavlink {
namespace mavlink_tof {
namespace msg {

/**
 * @brief DEVICE_STATE message
 *
 * Message with device info
 */
struct DEVICE_STATE : mavlink::Message {
    static constexpr msgid_t MSG_ID = 150;
    static constexpr size_t LENGTH = 25;
    static constexpr size_t MIN_LENGTH = 25;
    static constexpr uint8_t CRC_EXTRA = 42;
    static constexpr auto NAME = "DEVICE_STATE";


    int16_t pwm_value; /*< APD dc-dc PWM value, timer ticks */
    uint8_t pwm_state; /*< 0-manual mode, 1-auto feedback apd voltage mode */
    float apd_voltage_targ; /*< Target APD voltage in volts */
    float apd_voltage_curr; /*< Current APD voltage in volts */
    float las_voltage; /*< Laser voltage in volts */
    uint16_t voltage_mv; /*< Comparator threshold voltage in mv */
    uint16_t raw_tof_value; /*< Raw TOF distance value in bins */
    uint16_t raw_tof_width_value; /*< Raw TOF pulse width value in bins */
    uint16_t distance; /*< Distance in mm */
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
        ss << "  pwm_value: " << pwm_value << std::endl;
        ss << "  pwm_state: " << +pwm_state << std::endl;
        ss << "  apd_voltage_targ: " << apd_voltage_targ << std::endl;
        ss << "  apd_voltage_curr: " << apd_voltage_curr << std::endl;
        ss << "  las_voltage: " << las_voltage << std::endl;
        ss << "  voltage_mv: " << voltage_mv << std::endl;
        ss << "  raw_tof_value: " << raw_tof_value << std::endl;
        ss << "  raw_tof_width_value: " << raw_tof_width_value << std::endl;
        ss << "  distance: " << distance << std::endl;
        ss << "  state: " << state << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << apd_voltage_targ;              // offset: 0
        map << apd_voltage_curr;              // offset: 4
        map << las_voltage;                   // offset: 8
        map << pwm_value;                     // offset: 12
        map << voltage_mv;                    // offset: 14
        map << raw_tof_value;                 // offset: 16
        map << raw_tof_width_value;           // offset: 18
        map << distance;                      // offset: 20
        map << state;                         // offset: 22
        map << pwm_state;                     // offset: 24
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> apd_voltage_targ;              // offset: 0
        map >> apd_voltage_curr;              // offset: 4
        map >> las_voltage;                   // offset: 8
        map >> pwm_value;                     // offset: 12
        map >> voltage_mv;                    // offset: 14
        map >> raw_tof_value;                 // offset: 16
        map >> raw_tof_width_value;           // offset: 18
        map >> distance;                      // offset: 20
        map >> state;                         // offset: 22
        map >> pwm_state;                     // offset: 24
    }
};

} // namespace msg
} // namespace mavlink_tof
} // namespace mavlink
