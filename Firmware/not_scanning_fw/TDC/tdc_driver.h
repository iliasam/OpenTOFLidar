#ifndef __TDC_DRIVER_H
#define __TDC_DRIVER_H

// Includes ------------------------------------------------------------------
#include "stdint.h"

// Exported types ------------------------------------------------------------
// Exported constants --------------------------------------------------------
void tdc_send_reset(void);
void tdc_test(void);
void tdc_configure(void);
void tdc_start_pulse(void);
void tdc_check_status(void);
uint16_t tdc_read_raw_value(void);
void tdc_read_two_registers(void);
void tdc_read_three_registers(void);

#endif //__TDC_DRIVER_H
