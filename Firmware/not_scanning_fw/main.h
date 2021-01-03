/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f30x.h"
#if defined(__ICCARM__) // IAR
  #include "intrinsics.h"
#endif

/* Exported types ------------------------------------------------------------*/
extern volatile uint32_t ms_tick;

/* Exported constants --------------------------------------------------------*/
// Bad communication with TDC after init
#define TDC_STATE_INIT_FAIL_FLAG        (1 << 0) //1
// No return signal was found
#define TDC_STATE_PULSE_TIMEOUT         (1 << 1) //2

// Wrong hits number from laser comparator
#define TDC_STATE_LASER_COMP_FAIL       (1 << 2)  //4

/* Exported macro ------------------------------------------------------------*/
#define START_TIMER(x, duration)  (x = (ms_tick + duration))
#define TIMER_ELAPSED(x)  ((ms_tick >= x) ? 1 : 0)

#if defined ( __ICCARM__ ) // IAR
    #define ENTER_CRITICAL(x)       x=__get_interrupt_state(); __disable_interrupt()
    #define LEAVE_CRITICAL(x)       __set_interrupt_state(x)

#elif defined (__CC_ARM) // KEIL
    #define ENTER_CRITICAL(x)       x=__disable_irq()
    #define LEAVE_CRITICAL(x)       if (!x) __enable_irq()
    #define NO_INIT                 __attribute__((zero_init))
#else
  #error ERROR
#endif

/* Exported functions ------------------------------------------------------- */
void parse_rx_uart_data(uint8_t data);

#endif /* __MAIN_H */
