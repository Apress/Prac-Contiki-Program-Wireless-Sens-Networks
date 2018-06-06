#include "contiki.h"
#include "dev/mycustom-sensor.h"
#include "dev/sky-sensors.h"


#define INPUT_CHANNEL   (1 << INCH_11)
#define INPUT_REFERENCE SREF_0
#define MYCUSTOM_MEM    ADC12MEM0

const struct sensors_sensor mycustom_sensor;
/*---------------------------------------------------------------------------*/
static int
value(int type)
{
  switch(type) {    
    case MY_CUSTOM_SENSOR:
        return MYCUSTOM_MEM;
  }

  return 0;
}
/*---------------------------------------------------------------------------*/
static int
configure(int type, int c)
{
  return sky_sensors_configure(INPUT_CHANNEL, INPUT_REFERENCE, type, c);
}
/*---------------------------------------------------------------------------*/
static int
status(int type)
{
  return sky_sensors_status(INPUT_CHANNEL, type);
}
/*---------------------------------------------------------------------------*/
SENSORS_SENSOR(mycustom_sensor, "MYCUSTOMSENSOR", value, configure, status);
