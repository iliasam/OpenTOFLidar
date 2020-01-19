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
//OpenTOFLidar by iliasam 

#include <open_tof_lidar.h>
#include <mavlink_tof/mavlink.h>
#include <cmath>
#include <ros/ros.h>

namespace lidar_driver
{
  openTOFLidarDriver::openTOFLidarDriver(const std::string& port, uint32_t baud_rate, boost::asio::io_service& io): port_(port),
  baud_rate_(baud_rate), shutting_down_(false), serial_(io, port_) 
  {
    serial_.set_option(boost::asio::serial_port_base::baud_rate(baud_rate_));
    LidarStartAngleDeg = 50;
    LidarStopAngleDeg = 280;
    LidarCorrRotationDeg = 3.0;
  }
  
  void openTOFLidarDriver::SetStartStopAngles(uint16_t start_deg, uint16_t stop_deg)
  {
    LidarStartAngleDeg = start_deg;
    LidarStopAngleDeg = stop_deg;
  }
  
  void openTOFLidarDriver::SetCorrRotationAngle(double angle_deg)
  {
    LidarCorrRotationDeg = angle_deg;
  }

  void openTOFLidarDriver::poll(sensor_msgs::LaserScan::Ptr scan) 
  {
     
    uint8_t temp_char;
    bool got_scan = false;
    
    currScan = scan;
    
    while (!shutting_down_ && !got_scan)
    {
      boost::asio::read(serial_, boost::asio::buffer(&temp_char,1));
      got_scan = parseByte(temp_char);
    }
    
  }//end of poll function
  
  bool openTOFLidarDriver::parseByte(uint8_t newByte) 
  {
    uint8_t res = mavlink_parse_char(0, newByte, &mavlink_rx_message, &mavlink_status);
    
    if (res != 0)
    {
      if (mavlink_rx_message.msgid == MAVLINK_MSG_ID_LONG_PACKET)
      {
        mavlink_long_packet_t long_packet;
        mavlink_msg_long_packet_decode(&mavlink_rx_message, &long_packet);
        return ParseLongPacket(long_packet);
      }
    }
    return false;
  }
  
  void openTOFLidarDriver::ProcessLidarData(uint8_t* scanData, uint16_t dataSizeBytes)
  {
    uint16_t scanPointsCnt = dataSizeBytes / 2; // every point is uint16_t value
    
    double angularStep = 360.0 / scanPointsCnt;
    
    uint16_t scanValues[scanPointsCnt];
    memcpy(scanValues, scanData, dataSizeBytes);

    //currScan->angle_min = 0.0;
    //currScan->angle_max = 2.0 * M_PI;
    currScan->angle_min = -M_PI ;
    currScan->angle_max =  M_PI;
    
    currScan->angle_increment = angularStep * M_PI /  180.0;
    currScan->time_increment =  1.0/(scanPointsCnt * 15.0);//1 sec
    currScan->range_min = 0.05;
    currScan->range_max = 20.0;
    currScan->scan_time = 1.0/15.0;//seconds
    currScan->ranges.reserve(scanPointsCnt);
    currScan->intensities.reserve(scanPointsCnt);
    
    int i;
    
    double distBuf[scanPointsCnt];
    for (i = 0; i < scanPointsCnt; i++)
    {
      double dist_m = (double)scanValues[i] / 1000.0;
      double angleDeg = (double)i * angularStep;
      
      if ((angleDeg < (double)LidarStartAngleDeg) || (angleDeg > (double)LidarStopAngleDeg))
        dist_m = 0.0;
      
      double correctedAngleDeg = angleDeg + LidarCorrRotationDeg;
      if (correctedAngleDeg > 359.0)
        correctedAngleDeg = correctedAngleDeg - 359.0;
      uint16_t pos = round(correctedAngleDeg / angularStep);
      distBuf[pos] = dist_m;
    }
    
    for (i = 0; i < scanPointsCnt; i++)
    {
      currScan->ranges.push_back(distBuf[i]);
      currScan->intensities.push_back(0);
    }
  }
  
  // ***** Mavlink LongPacket parsing
  
  // Process current LongPacket
  bool openTOFLidarDriver::ProcessLongPacket()
  {
    if (longPacket.dataCode == 2) //scan data
    {
      uint16_t rxDataSize = longPacket.byteDataList.size();
      if (rxDataSize > 200)
      {
        uint8_t scanData[rxDataSize];
        std::copy(longPacket.byteDataList.begin(), longPacket.byteDataList.end(), scanData);
        ProcessLidarData(scanData, rxDataSize);
        return true;//got scan
      }
    }
    return false;
  }
  
  // Parsing subpacket
  bool openTOFLidarDriver::ParseLongPacket(mavlink_long_packet_t packet)
  {
    if (packet.packet_id != longPacket.packetId) //Only one packet now 
    {
      longPacket = AddNewLongPacket(packet);
      int res = LongPacketAddSubpacket(packet);

      if (res == 2)
      {
        //LongPacketReceived?.Invoke(longPacket);
        return ProcessLongPacket();
      }
    }
    else //id is equal
    {
      int res = LongPacketAddSubpacket(packet);

      if (res == 2)
      {
        //LongPacketReceived?.Invoke(longPacket);
        //ROS_ERROR("New Packet:%d", longPacket.packetId);
        //ROS_ERROR("size:%d", longPacket.byteDataList.size());
        return ProcessLongPacket();
      }
    }
    return false;
  }
  
  int openTOFLidarDriver::LongPacketAddSubpacket(mavlink_long_packet_t packet)
  {
    if (longPacket.packetId != packet.packet_id)
      return -1;

    //id is equal

    if (longPacket.dataCode != packet.data_code)
      return -2;

    //data_code is equal

    // Subpackets must go without skipping and repeats
    if ((longPacket.packetCnt != (packet.packet_cnt - 1)) && (packet.packet_cnt != 0))
    {
      return -3;
    }

    // Copy data
    int i;
    for (i = 0; i < packet.payload_size; i++)
    {
      longPacket.byteDataList.push_back(packet.data[i]);
    }

    int result = 1;

    if (packet.packet_cnt == (packet.total_cnt - 1))
    {
      // End of long packet is found
      result = 2;
    }

    longPacket.packetCnt = packet.packet_cnt;
    longPacket.packetsReceived++;

    return result;
  }
  
  openTOFLidarDriver::LongPacketStruct openTOFLidarDriver::AddNewLongPacket(mavlink_long_packet_t packet)
  {
    LongPacketStruct tmp_long_packet;

    if (packet.packet_cnt != 0)//not good
    {
      tmp_long_packet.dataCode = -1;//error
      return tmp_long_packet;
    }

    // Detected new ID - new long packet found
    tmp_long_packet.packetId = packet.packet_id;
    tmp_long_packet.totalCnt = packet.total_cnt;
    tmp_long_packet.dataCode = packet.data_code;
    tmp_long_packet.packetCnt = 0;
    tmp_long_packet.packetsReceived = 0;
    tmp_long_packet.byteDataList.clear();
    //tmp_long_packet.byteDataList = new List<byte> {};

    return tmp_long_packet;
  }
  
};//end of namespace
