/** @file
 *	@brief MAVLink comm testsuite protocol generated from mavlink_tof.xml
 *	@see http://mavlink.org
 */

#pragma once

#include <gtest/gtest.h>
#include "mavlink_tof.hpp"

#ifdef TEST_INTEROP
using namespace mavlink;
#undef MAVLINK_HELPER
#include "mavlink.h"
#endif


TEST(mavlink_tof, DATA_REQUEST)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::mavlink_tof::msg::DATA_REQUEST packet_in{};
    packet_in.data_type = 5;

    mavlink::mavlink_tof::msg::DATA_REQUEST packet1{};
    mavlink::mavlink_tof::msg::DATA_REQUEST packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.data_type, packet2.data_type);
}

#ifdef TEST_INTEROP
TEST(mavlink_tof_interop, DATA_REQUEST)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_data_request_t packet_c {
         5
    };

    mavlink::mavlink_tof::msg::DATA_REQUEST packet_in{};
    packet_in.data_type = 5;

    mavlink::mavlink_tof::msg::DATA_REQUEST packet2{};

    mavlink_msg_data_request_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.data_type, packet2.data_type);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(mavlink_tof, DEVICE_COMMAND)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::mavlink_tof::msg::DEVICE_COMMAND packet_in{};
    packet_in.cmd = 17;
    packet_in.value = 963497464;

    mavlink::mavlink_tof::msg::DEVICE_COMMAND packet1{};
    mavlink::mavlink_tof::msg::DEVICE_COMMAND packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.cmd, packet2.cmd);
    EXPECT_EQ(packet1.value, packet2.value);
}

#ifdef TEST_INTEROP
TEST(mavlink_tof_interop, DEVICE_COMMAND)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_device_command_t packet_c {
         963497464, 17
    };

    mavlink::mavlink_tof::msg::DEVICE_COMMAND packet_in{};
    packet_in.cmd = 17;
    packet_in.value = 963497464;

    mavlink::mavlink_tof::msg::DEVICE_COMMAND packet2{};

    mavlink_msg_device_command_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.cmd, packet2.cmd);
    EXPECT_EQ(packet_in.value, packet2.value);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(mavlink_tof, LONG_PACKET)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::mavlink_tof::msg::LONG_PACKET packet_in{};
    packet_in.data_code = 151;
    packet_in.packet_id = 17235;
    packet_in.packet_cnt = 17339;
    packet_in.total_cnt = 17443;
    packet_in.payload_size = 218;
    packet_in.data = {{ 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228 }};

    mavlink::mavlink_tof::msg::LONG_PACKET packet1{};
    mavlink::mavlink_tof::msg::LONG_PACKET packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.data_code, packet2.data_code);
    EXPECT_EQ(packet1.packet_id, packet2.packet_id);
    EXPECT_EQ(packet1.packet_cnt, packet2.packet_cnt);
    EXPECT_EQ(packet1.total_cnt, packet2.total_cnt);
    EXPECT_EQ(packet1.payload_size, packet2.payload_size);
    EXPECT_EQ(packet1.data, packet2.data);
}

#ifdef TEST_INTEROP
TEST(mavlink_tof_interop, LONG_PACKET)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_long_packet_t packet_c {
         17235, 17339, 17443, 151, 218, { 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228 }
    };

    mavlink::mavlink_tof::msg::LONG_PACKET packet_in{};
    packet_in.data_code = 151;
    packet_in.packet_id = 17235;
    packet_in.packet_cnt = 17339;
    packet_in.total_cnt = 17443;
    packet_in.payload_size = 218;
    packet_in.data = {{ 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228 }};

    mavlink::mavlink_tof::msg::LONG_PACKET packet2{};

    mavlink_msg_long_packet_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.data_code, packet2.data_code);
    EXPECT_EQ(packet_in.packet_id, packet2.packet_id);
    EXPECT_EQ(packet_in.packet_cnt, packet2.packet_cnt);
    EXPECT_EQ(packet_in.total_cnt, packet2.total_cnt);
    EXPECT_EQ(packet_in.payload_size, packet2.payload_size);
    EXPECT_EQ(packet_in.data, packet2.data);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(mavlink_tof, SET_APD_VOLTAGE)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::mavlink_tof::msg::SET_APD_VOLTAGE packet_in{};
    packet_in.pwm_value = 17443;
    packet_in.voltage = 17.0;

    mavlink::mavlink_tof::msg::SET_APD_VOLTAGE packet1{};
    mavlink::mavlink_tof::msg::SET_APD_VOLTAGE packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.pwm_value, packet2.pwm_value);
    EXPECT_EQ(packet1.voltage, packet2.voltage);
}

#ifdef TEST_INTEROP
TEST(mavlink_tof_interop, SET_APD_VOLTAGE)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_set_apd_voltage_t packet_c {
         17.0, 17443
    };

    mavlink::mavlink_tof::msg::SET_APD_VOLTAGE packet_in{};
    packet_in.pwm_value = 17443;
    packet_in.voltage = 17.0;

    mavlink::mavlink_tof::msg::SET_APD_VOLTAGE packet2{};

    mavlink_msg_set_apd_voltage_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.pwm_value, packet2.pwm_value);
    EXPECT_EQ(packet_in.voltage, packet2.voltage);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(mavlink_tof, SET_LASER_VOLTAGE)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::mavlink_tof::msg::SET_LASER_VOLTAGE packet_in{};
    packet_in.voltage = 17.0;

    mavlink::mavlink_tof::msg::SET_LASER_VOLTAGE packet1{};
    mavlink::mavlink_tof::msg::SET_LASER_VOLTAGE packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.voltage, packet2.voltage);
}

#ifdef TEST_INTEROP
TEST(mavlink_tof_interop, SET_LASER_VOLTAGE)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_set_laser_voltage_t packet_c {
         17.0
    };

    mavlink::mavlink_tof::msg::SET_LASER_VOLTAGE packet_in{};
    packet_in.voltage = 17.0;

    mavlink::mavlink_tof::msg::SET_LASER_VOLTAGE packet2{};

    mavlink_msg_set_laser_voltage_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.voltage, packet2.voltage);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(mavlink_tof, SET_COMP_THRESHOLD)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::mavlink_tof::msg::SET_COMP_THRESHOLD packet_in{};
    packet_in.voltage_mv = 17235;

    mavlink::mavlink_tof::msg::SET_COMP_THRESHOLD packet1{};
    mavlink::mavlink_tof::msg::SET_COMP_THRESHOLD packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.voltage_mv, packet2.voltage_mv);
}

#ifdef TEST_INTEROP
TEST(mavlink_tof_interop, SET_COMP_THRESHOLD)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_set_comp_threshold_t packet_c {
         17235
    };

    mavlink::mavlink_tof::msg::SET_COMP_THRESHOLD packet_in{};
    packet_in.voltage_mv = 17235;

    mavlink::mavlink_tof::msg::SET_COMP_THRESHOLD packet2{};

    mavlink_msg_set_comp_threshold_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.voltage_mv, packet2.voltage_mv);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(mavlink_tof, START_BATCH_MEASUREMENT)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::mavlink_tof::msg::START_BATCH_MEASUREMENT packet_in{};
    packet_in.length = 17235;

    mavlink::mavlink_tof::msg::START_BATCH_MEASUREMENT packet1{};
    mavlink::mavlink_tof::msg::START_BATCH_MEASUREMENT packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.length, packet2.length);
}

#ifdef TEST_INTEROP
TEST(mavlink_tof_interop, START_BATCH_MEASUREMENT)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_start_batch_measurement_t packet_c {
         17235
    };

    mavlink::mavlink_tof::msg::START_BATCH_MEASUREMENT packet_in{};
    packet_in.length = 17235;

    mavlink::mavlink_tof::msg::START_BATCH_MEASUREMENT packet2{};

    mavlink_msg_start_batch_measurement_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.length, packet2.length);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(mavlink_tof, START_CORR_BATCH_MEASUREMENT)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::mavlink_tof::msg::START_CORR_BATCH_MEASUREMENT packet_in{};
    packet_in.length = 17235;

    mavlink::mavlink_tof::msg::START_CORR_BATCH_MEASUREMENT packet1{};
    mavlink::mavlink_tof::msg::START_CORR_BATCH_MEASUREMENT packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.length, packet2.length);
}

#ifdef TEST_INTEROP
TEST(mavlink_tof_interop, START_CORR_BATCH_MEASUREMENT)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_start_corr_batch_measurement_t packet_c {
         17235
    };

    mavlink::mavlink_tof::msg::START_CORR_BATCH_MEASUREMENT packet_in{};
    packet_in.length = 17235;

    mavlink::mavlink_tof::msg::START_CORR_BATCH_MEASUREMENT packet2{};

    mavlink_msg_start_corr_batch_measurement_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.length, packet2.length);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(mavlink_tof, SET_WIDTH_CORR_COEFF)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::mavlink_tof::msg::SET_WIDTH_CORR_COEFF packet_in{};
    packet_in.coeff_a = 17.0;
    packet_in.coeff_b = 45.0;

    mavlink::mavlink_tof::msg::SET_WIDTH_CORR_COEFF packet1{};
    mavlink::mavlink_tof::msg::SET_WIDTH_CORR_COEFF packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.coeff_a, packet2.coeff_a);
    EXPECT_EQ(packet1.coeff_b, packet2.coeff_b);
}

#ifdef TEST_INTEROP
TEST(mavlink_tof_interop, SET_WIDTH_CORR_COEFF)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_set_width_corr_coeff_t packet_c {
         17.0, 45.0
    };

    mavlink::mavlink_tof::msg::SET_WIDTH_CORR_COEFF packet_in{};
    packet_in.coeff_a = 17.0;
    packet_in.coeff_b = 45.0;

    mavlink::mavlink_tof::msg::SET_WIDTH_CORR_COEFF packet2{};

    mavlink_msg_set_width_corr_coeff_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.coeff_a, packet2.coeff_a);
    EXPECT_EQ(packet_in.coeff_b, packet2.coeff_b);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(mavlink_tof, SET_REF_OFFSET)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::mavlink_tof::msg::SET_REF_OFFSET packet_in{};
    packet_in.dist_value = 17235;

    mavlink::mavlink_tof::msg::SET_REF_OFFSET packet1{};
    mavlink::mavlink_tof::msg::SET_REF_OFFSET packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.dist_value, packet2.dist_value);
}

#ifdef TEST_INTEROP
TEST(mavlink_tof_interop, SET_REF_OFFSET)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_set_ref_offset_t packet_c {
         17235
    };

    mavlink::mavlink_tof::msg::SET_REF_OFFSET packet_in{};
    packet_in.dist_value = 17235;

    mavlink::mavlink_tof::msg::SET_REF_OFFSET packet2{};

    mavlink_msg_set_ref_offset_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.dist_value, packet2.dist_value);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(mavlink_tof, SET_MOTOR_DUTY)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::mavlink_tof::msg::SET_MOTOR_DUTY packet_in{};
    packet_in.duty = 17235;

    mavlink::mavlink_tof::msg::SET_MOTOR_DUTY packet1{};
    mavlink::mavlink_tof::msg::SET_MOTOR_DUTY packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.duty, packet2.duty);
}

#ifdef TEST_INTEROP
TEST(mavlink_tof_interop, SET_MOTOR_DUTY)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_set_motor_duty_t packet_c {
         17235
    };

    mavlink::mavlink_tof::msg::SET_MOTOR_DUTY packet_in{};
    packet_in.duty = 17235;

    mavlink::mavlink_tof::msg::SET_MOTOR_DUTY packet2{};

    mavlink_msg_set_motor_duty_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.duty, packet2.duty);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(mavlink_tof, SET_MOTOR_SPEED)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::mavlink_tof::msg::SET_MOTOR_SPEED packet_in{};
    packet_in.speed = 17.0;

    mavlink::mavlink_tof::msg::SET_MOTOR_SPEED packet1{};
    mavlink::mavlink_tof::msg::SET_MOTOR_SPEED packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.speed, packet2.speed);
}

#ifdef TEST_INTEROP
TEST(mavlink_tof_interop, SET_MOTOR_SPEED)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_set_motor_speed_t packet_c {
         17.0
    };

    mavlink::mavlink_tof::msg::SET_MOTOR_SPEED packet_in{};
    packet_in.speed = 17.0;

    mavlink::mavlink_tof::msg::SET_MOTOR_SPEED packet2{};

    mavlink_msg_set_motor_speed_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.speed, packet2.speed);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(mavlink_tof, DEVICE_STATE)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::mavlink_tof::msg::DEVICE_STATE packet_in{};
    packet_in.pwm_value = 17859;
    packet_in.pwm_state = 77;
    packet_in.apd_voltage_targ = 17.0;
    packet_in.apd_voltage_curr = 45.0;
    packet_in.las_voltage = 73.0;
    packet_in.voltage_mv = 17963;
    packet_in.raw_tof_value = 18067;
    packet_in.raw_tof_width_value = 18171;
    packet_in.distance = 18275;
    packet_in.state = 18379;

    mavlink::mavlink_tof::msg::DEVICE_STATE packet1{};
    mavlink::mavlink_tof::msg::DEVICE_STATE packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.pwm_value, packet2.pwm_value);
    EXPECT_EQ(packet1.pwm_state, packet2.pwm_state);
    EXPECT_EQ(packet1.apd_voltage_targ, packet2.apd_voltage_targ);
    EXPECT_EQ(packet1.apd_voltage_curr, packet2.apd_voltage_curr);
    EXPECT_EQ(packet1.las_voltage, packet2.las_voltage);
    EXPECT_EQ(packet1.voltage_mv, packet2.voltage_mv);
    EXPECT_EQ(packet1.raw_tof_value, packet2.raw_tof_value);
    EXPECT_EQ(packet1.raw_tof_width_value, packet2.raw_tof_width_value);
    EXPECT_EQ(packet1.distance, packet2.distance);
    EXPECT_EQ(packet1.state, packet2.state);
}

#ifdef TEST_INTEROP
TEST(mavlink_tof_interop, DEVICE_STATE)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_device_state_t packet_c {
         17.0, 45.0, 73.0, 17859, 17963, 18067, 18171, 18275, 18379, 77
    };

    mavlink::mavlink_tof::msg::DEVICE_STATE packet_in{};
    packet_in.pwm_value = 17859;
    packet_in.pwm_state = 77;
    packet_in.apd_voltage_targ = 17.0;
    packet_in.apd_voltage_curr = 45.0;
    packet_in.las_voltage = 73.0;
    packet_in.voltage_mv = 17963;
    packet_in.raw_tof_value = 18067;
    packet_in.raw_tof_width_value = 18171;
    packet_in.distance = 18275;
    packet_in.state = 18379;

    mavlink::mavlink_tof::msg::DEVICE_STATE packet2{};

    mavlink_msg_device_state_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.pwm_value, packet2.pwm_value);
    EXPECT_EQ(packet_in.pwm_state, packet2.pwm_state);
    EXPECT_EQ(packet_in.apd_voltage_targ, packet2.apd_voltage_targ);
    EXPECT_EQ(packet_in.apd_voltage_curr, packet2.apd_voltage_curr);
    EXPECT_EQ(packet_in.las_voltage, packet2.las_voltage);
    EXPECT_EQ(packet_in.voltage_mv, packet2.voltage_mv);
    EXPECT_EQ(packet_in.raw_tof_value, packet2.raw_tof_value);
    EXPECT_EQ(packet_in.raw_tof_width_value, packet2.raw_tof_width_value);
    EXPECT_EQ(packet_in.distance, packet2.distance);
    EXPECT_EQ(packet_in.state, packet2.state);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(mavlink_tof, MOTOR_STATE)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::mavlink_tof::msg::MOTOR_STATE packet_in{};
    packet_in.pwm_duty = 17651;
    packet_in.motor_speed = 17.0;
    packet_in.setted_pwm_duty = 17755;
    packet_in.setted_motor_speed = 45.0;
    packet_in.state = 17859;

    mavlink::mavlink_tof::msg::MOTOR_STATE packet1{};
    mavlink::mavlink_tof::msg::MOTOR_STATE packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.pwm_duty, packet2.pwm_duty);
    EXPECT_EQ(packet1.motor_speed, packet2.motor_speed);
    EXPECT_EQ(packet1.setted_pwm_duty, packet2.setted_pwm_duty);
    EXPECT_EQ(packet1.setted_motor_speed, packet2.setted_motor_speed);
    EXPECT_EQ(packet1.state, packet2.state);
}

#ifdef TEST_INTEROP
TEST(mavlink_tof_interop, MOTOR_STATE)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_motor_state_t packet_c {
         17.0, 45.0, 17651, 17755, 17859
    };

    mavlink::mavlink_tof::msg::MOTOR_STATE packet_in{};
    packet_in.pwm_duty = 17651;
    packet_in.motor_speed = 17.0;
    packet_in.setted_pwm_duty = 17755;
    packet_in.setted_motor_speed = 45.0;
    packet_in.state = 17859;

    mavlink::mavlink_tof::msg::MOTOR_STATE packet2{};

    mavlink_msg_motor_state_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.pwm_duty, packet2.pwm_duty);
    EXPECT_EQ(packet_in.motor_speed, packet2.motor_speed);
    EXPECT_EQ(packet_in.setted_pwm_duty, packet2.setted_pwm_duty);
    EXPECT_EQ(packet_in.setted_motor_speed, packet2.setted_motor_speed);
    EXPECT_EQ(packet_in.state, packet2.state);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif
