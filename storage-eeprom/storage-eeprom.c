#include "contiki.h"
#include "dev/eeprom.h"

#include <stdio.h>              /* For printf() */


void
erase_all_content_eeprom()
{
  static eeprom_addr_t addr = 0;

  for(addr = 0; addr < EEPROM_SIZE; ++addr) {
    eeprom_write(addr, 0, 1);
  }
}

/*---------------------------------------------------------------------------*/
PROCESS(eeprom_demo_process, "EEPROM Demo Process");
AUTOSTART_PROCESSES(&eeprom_demo_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(eeprom_demo_process, ev, data)
{
  uint8_t address =  0x0A;
  static uint8_t content = 15;
  uint8_t byte;

  PROCESS_BEGIN();

  printf("EEPROM Size = %d bytes\n", EEPROM_SIZE);
  printf("Erase all EEPROM content\n");
  erase_all_content_eeprom();

  printf("Write data into EEPROM Address 0x%x : 0x%x\n",address, content);
  eeprom_write(address, &content, 1);

  byte = 0;
  eeprom_read(address, &byte, 1);
  printf("Read EEPROM 0x%x : 0x%x\n", address, byte);


  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
