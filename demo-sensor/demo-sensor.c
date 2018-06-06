

#include "contiki.h"
#include "sys/etimer.h"
#include "mysensor.h"
#include <stdio.h> 

PROCESS(sensor_process, "Sensor process");
AUTOSTART_PROCESSES(&sensor_process);

static struct etimer timer;

PROCESS_THREAD(sensor_process, ev, data)
{
  PROCESS_BEGIN();

  printf("Demo Virtual Sensor\n");
  while(1) {
    etimer_set(&timer, 3 * CLOCK_SECOND);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));

    struct Sensor temp = read_temperature();
    printf("%s: %.2f\n", temp.name, temp.value);
    struct Sensor hum = read_humidity();
    printf("%s: %.2f\n", hum.name, hum.value);
    printf("------------\n");
  }
  
  PROCESS_END();
}
