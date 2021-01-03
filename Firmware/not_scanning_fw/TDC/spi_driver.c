//Written for TDC-GP21

// Includes ------------------------------------------------------------------
#include "spi_driver.h"

#include "stm32f30x_gpio.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_spi.h"


// Private typedef -----------------------------------------------------------
// Private define ------------------------------------------------------------
// Private variables ---------------------------------------------------------

// Private function prototypes -----------------------------------------------
void init_tdc_spi(void);

// Private functions ---------------------------------------------------------

// Send one byte to the TDC
void send_opcode_to_tdc(uint8_t opcode)
{
  volatile uint8_t tmp = TDC_SPI_NAME->DR;//clear RXNE
  
  //CSN to LOW
  GPIO_WriteBit(TDC_SPI_CSN_PORT, TDC_SPI_CSN, Bit_RESET);
  
  while (SPI_I2S_GetFlagStatus(TDC_SPI_NAME, SPI_I2S_FLAG_TXE) == RESET);
  SPI_SendData8(TDC_SPI_NAME, opcode);
  //Wait for all data to be tansmitted
  while (SPI_I2S_GetFlagStatus(TDC_SPI_NAME, SPI_I2S_FLAG_RXNE) == RESET);
  while (SPI_I2S_GetFlagStatus(TDC_SPI_NAME, SPI_I2S_FLAG_BSY) == SET);

  //CSN to HIGH
  GPIO_WriteBit(TDC_SPI_CSN_PORT, TDC_SPI_CSN, Bit_SET);
}

// Write data to the 32-bit register
void tdc_write_register(uint8_t opcode_address,  uint32_t reg_data)
{
  uint8_t tmp_data;
  
  //CSN to LOW
  GPIO_WriteBit(TDC_SPI_CSN_PORT, TDC_SPI_CSN, Bit_RESET);
  
  //Send opcode
  while (SPI_I2S_GetFlagStatus(TDC_SPI_NAME, SPI_I2S_FLAG_TXE) == RESET);
  SPI_SendData8(TDC_SPI_NAME, opcode_address);
  
  //3 bytes from 4 bytes
  for (uint8_t i = 0; i < 3; i++)
  {
    while (SPI_I2S_GetFlagStatus(TDC_SPI_NAME, SPI_I2S_FLAG_TXE) == RESET);
    //Sending upper byte
    tmp_data = (uint8_t)((reg_data >> 24) & 0xFF);
    SPI_SendData8(TDC_SPI_NAME, tmp_data);
    reg_data = reg_data << 8;
  }
  
  while (SPI_I2S_GetFlagStatus(TDC_SPI_NAME, SPI_I2S_FLAG_TXE) == RESET);
  volatile uint8_t tmp = TDC_SPI_NAME->DR;//clear RXNE
  tmp_data = (uint8_t)((reg_data >> 24) & 0xFF);
  SPI_SendData8(TDC_SPI_NAME, tmp_data);
  while (SPI_I2S_GetFlagStatus(TDC_SPI_NAME, SPI_I2S_FLAG_RXNE) == RESET);
  while (SPI_I2S_GetFlagStatus(TDC_SPI_NAME, SPI_I2S_FLAG_BSY) == SET);
  
  //CSN to HIGH
  GPIO_WriteBit(TDC_SPI_CSN_PORT, TDC_SPI_CSN, Bit_SET);
}

uint32_t tdc_read_n_bytes(uint8_t n_bytes, uint8_t opcode_address)
{
  uint32_t read_result = 0;
  
  //CSN to LOW
  GPIO_WriteBit(TDC_SPI_CSN_PORT, TDC_SPI_CSN, Bit_RESET);
  
  //Send opcode
  while (SPI_I2S_GetFlagStatus(TDC_SPI_NAME, SPI_I2S_FLAG_TXE) == RESET);
  SPI_SendData8(TDC_SPI_NAME, opcode_address);
  
  //Begin read
  while (SPI_I2S_GetFlagStatus(TDC_SPI_NAME, SPI_I2S_FLAG_BSY) == SET);
  
  volatile uint8_t tmp;
  while (SPI_I2S_GetFlagStatus(TDC_SPI_NAME, SPI_I2S_FLAG_RXNE) == SET)
  {
    tmp = TDC_SPI_NAME->DR;//clear RXNE
  }
  
  for (uint8_t i = 0; i < n_bytes; i++)
  {
    SPI_SendData8(TDC_SPI_NAME, 0xFF);
    // Wait until RX buffer is not empty, then read the received data
    while (SPI_I2S_GetFlagStatus(TDC_SPI_NAME, SPI_I2S_FLAG_RXNE) == RESET);
    
    read_result = read_result << 8;
    read_result |= (uint32_t)SPI_ReceiveData8(TDC_SPI_NAME); //  Read
  }
  while (SPI_I2S_GetFlagStatus(TDC_SPI_NAME, SPI_I2S_FLAG_BSY) == SET);
  
  //CSN to HIGH
  GPIO_WriteBit(TDC_SPI_CSN_PORT, TDC_SPI_CSN, Bit_SET);

  return read_result;
}


void init_tdc_periph(void)
{
  init_tdc_spi();
}

void init_tdc_spi(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  SPI_InitTypeDef SPI_InitStruct;
  
  //GPIO clk must be already enabled!
  GPIO_InitStruct.GPIO_Pin =  TDC_SPI_MOSI | TDC_SPI_MISO | TDC_SPI_SCK;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(TDC_SPI_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.GPIO_Pin =  TDC_SPI_CSN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_Init(TDC_SPI_CSN_PORT, &GPIO_InitStruct);
  GPIO_WriteBit(TDC_SPI_CSN_PORT, TDC_SPI_CSN, Bit_SET);
  
  GPIO_PinAFConfig(TDC_SPI_PORT, TDC_SPI_MOSI_AF, TDC_SPI_AFIO);
  GPIO_PinAFConfig(TDC_SPI_PORT, TDC_SPI_MISO_AF, TDC_SPI_AFIO);
  GPIO_PinAFConfig(TDC_SPI_PORT, TDC_SPI_SCK_AF,  TDC_SPI_AFIO);
  
  RCC_APB1PeriphClockCmd(TDC_SPI_CLK, ENABLE);
  
  // CPOL = 0 --> clock is low when idle
  // CPHA = 0 --> data is sampled at the first edge
  
  SPI_StructInit(&SPI_InitStruct);
  SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
  SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
  SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;// data is transmitted MSB first
  SPI_Init(TDC_SPI_NAME, &SPI_InitStruct);
  SPI_RxFIFOThresholdConfig(TDC_SPI_NAME, SPI_RxFIFOThreshold_QF);
  
  SPI_Cmd(TDC_SPI_NAME, ENABLE);
}

//Read register - upper 16 bits
uint32_t tdc_read_register_upper(uint8_t opcode_address)
{
  uint32_t read_result = tdc_read_n_bytes(2, opcode_address);
  return read_result;
}
