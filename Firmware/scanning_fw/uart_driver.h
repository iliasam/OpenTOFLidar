#ifndef __UART_DRIVER_H
#define __UART_DRIVER_H

// Includes ------------------------------------------------------------------
#include "stdint.h"

// Exported types ------------------------------------------------------------


// Exported constants --------------------------------------------------------

void uart_driver_init(void);
void uart_driver_send_byte(uint8_t data);
uint8_t uart_driver_add_data_for_tx(uint8_t* data, uint16_t size);
void uart_driver_add_rx_byte(uint8_t rx_byte);
void uart_driver_process(void);
void uart_driver_tx_process(void);


#endif //__UART_DRIVER_H
