#ifndef __SPI_DRIVER_H
#define __SPI_DRIVER_H

// Includes ------------------------------------------------------------------
#include "stdint.h"
#include "config.h"

// Exported types ------------------------------------------------------------
// Exported constants --------------------------------------------------------

void init_tdc_periph(void);
void send_opcode_to_tdc(uint8_t opcode);
void tdc_write_register(uint8_t opcode_address,  uint32_t reg_data);
uint32_t tdc_read_n_bytes(uint8_t n_bytes, uint8_t opcode_address);
uint32_t tdc_read_register_upper(uint8_t opcode_address);


#endif //__SPI_DRIVER_H
