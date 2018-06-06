#include "contiki.h"
#include "dev/sht11/sht11-sensor.h"

#include <math.h>
#include <stdio.h> /* For printf() */
/*---------------------------------------------------------------------------*/
PROCESS(sensing_process, "Sensing process");
AUTOSTART_PROCESSES(&sensing_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(sensing_process, ev, data)
{
  static struct etimer et;
  static int val;
  static float s = 0;
  static int dec;
  static float frac;

  PROCESS_BEGIN();

  printf("Demo sensing...\n");
  while(1)
  {
	  etimer_set(&et, CLOCK_SECOND * 5);
    SENSORS_ACTIVATE(sht11_sensor);
        
	  PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

    val = sht11_sensor.value(SHT11_SENSOR_TEMP);
    if(val != -1) 
    {
      s= ((0.01*val) - 39.60);
      dec = s;
      frac = s - dec;
      // print float data
      printf("Temperature=%d.%02u C . VAL=%d\n", dec, (unsigned int)(frac * 100),val);               
    }

    val=sht11_sensor.value(SHT11_SENSOR_HUMIDITY);
    if(val != -1) 
    {
      s= (((0.0405*val) - 4) + ((-2.8 * 0.000001)*(pow(val,2))));  
      dec = s;
      frac = s - dec;
      // print float data
      printf("Humidity=%d.%02u %% . VAL=%d\n", dec, (unsigned int)(frac * 100),val);               
    }

    etimer_reset(&et);
    SENSORS_DEACTIVATE(sht11_sensor);

  } 
  
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
