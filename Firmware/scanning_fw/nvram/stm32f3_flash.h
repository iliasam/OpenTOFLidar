/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F3_FLASH_H
#define __STM32F3_FLASH_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f30x.h"
#include "config.h"

/* Exported types ------------------------------------------------------------*/
#define FLASH_BYTES_PER_KB              1024
#define FLASH_SECTOR_SIZE               2048

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void flash_erase_sector(uint8_t sector_idx);
void flash_write(uint32_t address_dst, uint8_t *buf, uint16_t size);
void flash_read(uint32_t src_addr, uint8_t *buf, uint16_t size);

#endif /* __STM32F3_FLASH_H */
