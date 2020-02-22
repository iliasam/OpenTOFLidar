#include "fifo_functions.h"
#include "main.h"

// Defines ********************************************************************

// Functions ******************************************************************

// Initialize FIFO with given values
// data_buffer - pointer to the buffer to store data
// size - size of that buffer
void fifo_init_struct(fifo_struct_t* fifo, uint8_t* data_buffer, uint16_t size)
{
  fifo->fifo_data = data_buffer;
  fifo->fifo_size = size;
  fifo->read_ptr = 0;
  fifo->write_ptr = 0;
  fifo->fifo_count = 0;
}

// Add "byte" to FIFO
// Returns 0 if addition fails
uint8_t fifo_add_byte(fifo_struct_t* fifo, uint8_t value)
{
  uint8_t result = 0;
  uint32_t save;
  ENTER_CRITICAL(save);
  
  if (fifo->fifo_count >= fifo->fifo_size)
  {
    result = 0;
  }
  else
  {
    if (fifo->write_ptr >= fifo->fifo_size)
      fifo->write_ptr = 0;
    
    fifo->fifo_data[fifo->write_ptr] = value;
    fifo->write_ptr++;
    fifo->fifo_count++;
    result = 1;
  }
  
  LEAVE_CRITICAL(save);
  return result;
}

// Returns 0 if addition fails
uint8_t fifo_add_data(fifo_struct_t* fifo, uint8_t* data, uint16_t size)
{
  uint16_t fifo_available = fifo->fifo_size - fifo->fifo_count;
  if (size > fifo_available)
    return 0;
  
  uint32_t save;
  ENTER_CRITICAL(save);
  for (uint16_t i = 0; i < size; i++)
    fifo_add_byte(fifo, data[i]);
  LEAVE_CRITICAL(save);
  return 1;
}

// Return number of elements in FIFO
uint16_t fifo_get_count(fifo_struct_t* fifo)
{
  return fifo->fifo_count;
}

// Get one byte from FIFO
// Place readed value to "value" pointer
// Returns 0 if nothing to read
uint8_t fifo_get_byte(fifo_struct_t* fifo, uint8_t* value)
{
  uint8_t result = 0;
  uint32_t save;
  ENTER_CRITICAL(save);
  
  if (fifo->fifo_count == 0)
  {
    result = 0;
  }
  else
  {
    *value = fifo->fifo_data[fifo->read_ptr];
    fifo->fifo_count--;
    
    fifo->read_ptr++;
    if (fifo->read_ptr >= fifo->fifo_size)
      fifo->read_ptr = 0;
    
    result = 1;
  }
  
  LEAVE_CRITICAL(save);
  return result;
  
}
