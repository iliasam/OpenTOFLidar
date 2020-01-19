/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2011, Eric Perko, Chad Rockey
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Case Western Reserve University nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

#include <sensor_msgs/LaserScan.h>
#include <mavlink_tof/mavlink.h>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <string>

namespace lidar_driver {
    class openTOFLidarDriver 
    {
        public:
            struct LongPacketStruct
            {
                int packetId;
                int totalCnt;
                int dataCode;

                int packetCnt;
                int packetsReceived;
                std::list<uint8_t> byteDataList;
                //List<byte> byteDataList;
            };
            
            /**
              * @brief Constructs a new openTOFLidarDriver attached to the given serial port
              * @param port The string for the serial port device to attempt to connect to, e.g. "/dev/ttyUSB0"
              * @param baud_rate The baud rate to open the serial port at.
              * @param io Boost ASIO IO Service to use when creating the serial port object
              */
            openTOFLidarDriver(const std::string& port, uint32_t baud_rate, boost::asio::io_service& io);

            /**
              * @brief Default destructor
              */
            ~openTOFLidarDriver() {};

            /**
              * @brief Poll the laser to get a new scan. Blocks until a complete new scan is received or close is called.
              * @param scan LaserScan message pointer to fill in with the scan. The caller is responsible for filling in the ROS timestamp and frame_id
              */
            void poll(sensor_msgs::LaserScan::Ptr scan);

            /**
              * @brief Close the driver down and prevent the polling loop from advancing
              */
            void close() { shutting_down_ = true; };

            bool parseByte(uint8_t newByte);
        

            LongPacketStruct AddNewLongPacket(mavlink_long_packet_t packet);
            int LongPacketAddSubpacket(mavlink_long_packet_t packet);
            bool ParseLongPacket(mavlink_long_packet_t packet);
            void ProcessLidarData(uint8_t* scanData, uint16_t dataSizeBytes);
            bool ProcessLongPacket();
            void SetStartStopAngles(uint16_t start_deg, uint16_t stop_deg);
            void SetCorrRotationAngle(double angle_deg);
            

        private:
            std::string port_; ///< @brief The serial port the driver is attached to
            uint32_t baud_rate_; ///< @brief The baud rate for the serial connection
            bool shutting_down_; ///< @brief Flag for whether the driver is supposed to be shutting down or not
            boost::asio::serial_port serial_; ///< @brief Actual serial port object
            
            sensor_msgs::LaserScan::Ptr currScan;
            uint16_t LidarStartAngleDeg;
            uint16_t LidarStopAngleDeg;
            double LidarCorrRotationDeg;///< @brief Additional scan rotation
            
            mavlink_message_t mavlink_rx_message;
            mavlink_status_t mavlink_status;
            
            // LongPacket Data
            LongPacketStruct longPacket;
    };
};
