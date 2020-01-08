using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using MavLink;

namespace LidarScanningTest1
{
    class MavlinkLongPacketClass
    {
        public struct LongPacketStruct
        {
            public int packetId;
            public int totalCnt;
            public int dataCode;
            /// Number of previous subpacket
            public int packetCnt;
            public int packetsReceived;
            public List<byte> byteDataList;
        }

        LongPacketStruct longPacket = new LongPacketStruct(); //Only one now

        public event LongPackerReceivedHandler LongPacketReceived;
        public delegate void LongPackerReceivedHandler(LongPacketStruct rxPacket);

        /// <summary>
        /// Add new packet for parsing
        /// </summary>
        /// <param name="packet"></param>
        public void AddPacket(MavLink.Msg_long_packet packet)
        {
            //System.Diagnostics.Debug.WriteLine($"Packet received");
            if (packet.packet_id != longPacket.packetId) //Only one packet now 
            {
                longPacket = AddNewLongPacket(packet);
                int res = LongPacketAddSubpacket(ref longPacket, packet);
                //System.Diagnostics.Debug.WriteLine($"add result: {res} at packet {packet.packet_cnt}");

                if (res == 2)
                {
                    LongPacketReceived?.Invoke(longPacket);
                }
            }
            else //id is equal
            {
                int res = LongPacketAddSubpacket(ref longPacket, packet);
                //System.Diagnostics.Debug.WriteLine($"add result: {res} at packet {packet.packet_cnt}");

                if (res == 2)
                {
                    LongPacketReceived?.Invoke(longPacket);
                }
            }
        }

        /// <summary>
        /// Add data to long packet
        /// </summary>
        /// <param name="longPacket"></param>
        /// <param name="packet"></param>
        /// <returns></returns>
        int LongPacketAddSubpacket(ref LongPacketStruct longPacket, MavLink.Msg_long_packet packet)
        {
            if (longPacket.packetId != packet.packet_id)
                return -1;

            //id is equal

            if (longPacket.dataCode != packet.data_code)
                return -2;

            //data_code is equal

            // Сабпакеты должны идти подряд, без пропусков и повторений
            // Subpackets must go without skipping and repeats
            if ((longPacket.packetCnt != (packet.packet_cnt - 1)) && (packet.packet_cnt != 0))
            {
                return -3;
            }

            // Копируем данные
            // Copy data
            int i;
            for (i = 0; i < packet.payload_size; i++)
            {
                longPacket.byteDataList.Add(packet.data[i]);
            }

            int result = 1;

            //System.Diagnostics.Debug.WriteLine($"add cnt: {packet.packet_cnt}");

            if (packet.packet_cnt == (packet.total_cnt - 1))
            {
                // Найден конец большого пакета
                // End of long packet is found
                result = 2;
            }

            longPacket.packetCnt = packet.packet_cnt;
            longPacket.packetsReceived++;

            return result;
        }

        LongPacketStruct AddNewLongPacket(MavLink.Msg_long_packet packet)
        {
            LongPacketStruct tmp_long_packet = new LongPacketStruct();

            if (packet.packet_cnt != 0)
            {
                tmp_long_packet.dataCode = -1;//error
                return tmp_long_packet;
            }

            // Обнаружен новый ID - появился новый большой пакет
            // Detected new ID - new long packet found
            tmp_long_packet.packetId = packet.packet_id;
            tmp_long_packet.totalCnt = packet.total_cnt;
            tmp_long_packet.dataCode = packet.data_code;
            tmp_long_packet.packetCnt = 0;
            tmp_long_packet.packetsReceived = 0;
            tmp_long_packet.byteDataList = new List<byte> {};

            return tmp_long_packet;
        }

    }//end of class
}
