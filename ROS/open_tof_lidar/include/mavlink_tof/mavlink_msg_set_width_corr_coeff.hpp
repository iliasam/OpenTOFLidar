// MESSAGE SET_WIDTH_CORR_COEFF support class

#pragma once

namespace mavlink {
namespace mavlink_tof {
namespace msg {

/**
 * @brief SET_WIDTH_CORR_COEFF message
 *
 * Set coefficients for correcting width change
 */
struct SET_WIDTH_CORR_COEFF : mavlink::Message {
    static constexpr msgid_t MSG_ID = 105;
    static constexpr size_t LENGTH = 8;
    static constexpr size_t MIN_LENGTH = 8;
    static constexpr uint8_t CRC_EXTRA = 227;
    static constexpr auto NAME = "SET_WIDTH_CORR_COEFF";


    float coeff_a; /*< Coefficient A */
    float coeff_b; /*< Coefficient B */


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
        ss << "  coeff_a: " << coeff_a << std::endl;
        ss << "  coeff_b: " << coeff_b << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << coeff_a;                       // offset: 0
        map << coeff_b;                       // offset: 4
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> coeff_a;                       // offset: 0
        map >> coeff_b;                       // offset: 4
    }
};

} // namespace msg
} // namespace mavlink_tof
} // namespace mavlink
