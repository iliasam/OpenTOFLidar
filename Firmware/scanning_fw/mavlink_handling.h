#ifndef MAVLINK_HANDLING_H
#define MAVLINK_HANDLING_H

#include "config.h"
#include <stdint.h>

// Defines ********************************************************************

// Functions ******************************************************************
void mavlink_parse_byte(uint8_t value);
void mavlink_send_batch_data(void);
void mavlink_long_packet_sending_process(void);
void mavlink_send_scan_data(uint16_t* data_source, uint16_t points_cnt);

#endif
