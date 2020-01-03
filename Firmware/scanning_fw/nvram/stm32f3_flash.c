/* Includes ------------------------------------------------------------------*/
#include "stm32f3_flash.h"
#include "main.h"
#include "string.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define FLASH_FLAG_ALL     FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_PGERR
#define FLASH_SECTOR_ADDRESS_MSK        (FLASH_SECTOR_SIZE - 1)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

void flash_erase_sector(uint8_t sector_idx)
{
  uint32_t int_state;
  FLASH_Unlock();
  ENTER_CRITICAL(int_state);
  FLASH_ClearFlag(FLASH_FLAG_ALL);
  
  uint32_t address_dst = FLASH_BASE + FLASH_SECTOR_SIZE * sector_idx;
  FLASH_Status status = FLASH_ErasePage(address_dst);
  LEAVE_CRITICAL(int_state);
  FLASH_Lock();
}


// Write array starting from given address
// address_dst - write start address, bytes
// buf - pointer to data source
// size - array size, bytes
// Data could be written to a single sector several times
void flash_write(uint32_t address_dst, uint8_t *buf, uint16_t size)
{
  uint32_t int_state;
  FLASH_Unlock();
  FLASH_ClearFlag(FLASH_FLAG_ALL);
  
  // Write two bytes
  for (uint16_t i = 0; i < (size / sizeof(uint16_t)); i++)
  {
    ENTER_CRITICAL(int_state);
    
    FLASH_Status result = FLASH_ProgramHalfWord(address_dst, ((uint16_t*)buf)[i]);
    address_dst += sizeof(uint16_t);
    
    LEAVE_CRITICAL(int_state);
    
    if (result != FLASH_COMPLETE)
    {
      break;
    }
  }
  FLASH_Lock();
}


// src_addr - source address in flash
// buf - destination address (RAM)
// size - size of readed data
void flash_read(uint32_t src_addr, uint8_t *buf, uint16_t size)
{
    memcpy((void *)buf, (void *)src_addr, size);
}
