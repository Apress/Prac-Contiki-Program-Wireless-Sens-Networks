#include "contiki.h"
#include "dev/mycustom-sensor.h"

#include <stdio.h> /* For printf() */
/*---------------------------------------------------------------------------*/
PROCESS(sensing_process, "Sensing process");
AUTOSTART_PROCESSES(&sensing_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(sensing_process, ev, data)
{
  static struct etimer et;
  static int val;

  PROCESS_BEGIN();

  printf("Demo sensing...\n");
  while(1)
  {
	  etimer_set(&et, CLOCK_SECOND * 5);
    SENSORS_ACTIVATE(mycustom_sensor);
        
	  PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

    val = mycustom_sensor.value(MY_CUSTOM_SENSOR);
    if(val != -1) 
    {
      printf("CUSTOM SENSOR VAL=%d\n",val);               
    }

    etimer_reset(&et);
    SENSORS_DEACTIVATE(mycustom_sensor);

  } 
  
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
