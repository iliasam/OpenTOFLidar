// Includes ------------------------------------------------------------------
#include "uart_driver.h"
#include "config.h"

#include "stm32f30x_gpio.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_usart.h"

#include "fifo_functions.h"
#include "mavlink_handling.h"

// Private typedef -----------------------------------------------------------
// Private define ------------------------------------------------------------
// RX FIFO buffer size, bytes
#define UART_RX_FIFO_SIZE                     512

// TX FIFO buffer size, bytes
#define UART_TX_FIFO_SIZE                     512

// Private variables ---------------------------------------------------------
volatile uint8_t uart_rx_fifo_buf[UART_RX_FIFO_SIZE];
volatile uint8_t uart_tx_fifo_buf[UART_TX_FIFO_SIZE];

volatile fifo_struct_t uart_rx_fifo;
fifo_struct_t uart_tx_fifo;

// Private function prototypes -----------------------------------------------
void uart_driver_init_fifo(void);
void uart_driver_tx_process(void);

// Private functions ---------------------------------------------------------

void uart_driver_init(void)
{
  uart_driver_init_fifo();
    
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

  /* Configure USART Tx as alternate function  */
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

  GPIO_InitStructure.GPIO_Pin = UART_TX_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(UART_TX_GPIO, &GPIO_InitStructure);

  /* Configure USART Rx as alternate function  */
  GPIO_InitStructure.GPIO_Pin = UART_RX_PIN;
  GPIO_Init(UART_RX_GPIO, &GPIO_InitStructure);

  GPIO_PinAFConfig(UART_TX_GPIO, UART_TX_PIN_AF, UART_AFIO);
  GPIO_PinAFConfig(UART_RX_GPIO, UART_RX_PIN_AF, UART_AFIO);
      
  USART_DeInit(UART_NAME);
  USART_StructInit(&USART_InitStructure);
  USART_InitStructure.USART_BaudRate = UART_BAUD;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No ;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
  USART_Init(UART_NAME, &USART_InitStructure);
  USART_Cmd(UART_NAME, ENABLE);
  
  USART_OverrunDetectionConfig(UART_NAME, USART_OVRDetection_Disable);
  
  USART_ITConfig(UART_NAME, USART_IT_RXNE, ENABLE);
  NVIC_EnableIRQ(UART_RX_INT_NAME);
  
}

void uart_driver_init_fifo(void)
{
  fifo_init_struct(
      (fifo_struct_t*)&uart_rx_fifo, 
      (uint8_t*)uart_rx_fifo_buf, 
      sizeof(uart_rx_fifo_buf));
  
    fifo_init_struct(
      (fifo_struct_t*)&uart_tx_fifo, 
      (uint8_t*)uart_tx_fifo_buf, 
      sizeof(uart_tx_fifo_buf));
}

//Handling rx and tx
void uart_driver_process(void)
{
  uint8_t rx_byte;
  while (fifo_get_byte((fifo_struct_t*)&uart_rx_fifo, &rx_byte))
  {
    mavlink_parse_byte(rx_byte);
  }
  uart_driver_tx_process();
}

void uart_driver_tx_process(void)
{
  uint8_t tx_byte;
  while (fifo_get_byte((fifo_struct_t*)&uart_tx_fifo, &tx_byte))
  {
    uart_driver_send_byte(tx_byte);
  }
}

// Returns 0 if addition fails
uint8_t uart_driver_add_data_for_tx(uint8_t* data, uint16_t size)
{
  return fifo_add_data((fifo_struct_t*)&uart_tx_fifo, data, size);
}

void uart_driver_add_rx_byte(uint8_t rx_byte)
{
  fifo_add_byte((fifo_struct_t*)&uart_rx_fifo, rx_byte);
}

void uart_driver_send_byte(uint8_t data)
{
  while (USART_GetFlagStatus(UART_NAME, USART_FLAG_TXE) == RESET);
  USART_SendData(UART_NAME, (uint16_t)data);
}
