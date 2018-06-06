#include "contiki.h"
#include "leds.h"
#include "dev/button-sensor.h" 

#include <stdio.h> /* For printf() */
/*---------------------------------------------------------------------------*/
PROCESS(sensing_process, "Sensing process");
AUTOSTART_PROCESSES(&sensing_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(sensing_process, ev, data)
{
  PROCESS_BEGIN();

  printf("Demo actuating...\n");
  SENSORS_ACTIVATE(button_sensor);
  leds_off(LEDS_ALL);

  while(1)
  {
    PROCESS_WAIT_EVENT_UNTIL(ev == sensors_event &&
			     data == &button_sensor);

    leds_toggle(LEDS_BLUE);    
  }
  SENSORS_DEACTIVATE(button_sensor);   
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
