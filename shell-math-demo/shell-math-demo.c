#include "contiki.h"
#include "shell.h"
#include "serial-shell.h"
#include "collect-view.h"


/*---------------------------------------------------------------------------*/
PROCESS(sky_shell_process, "Sky Contiki shell");
AUTOSTART_PROCESSES(&sky_shell_process);
/*---------------------------------------------------------------------------*/
#define WITH_PERIODIC_DEBUG 0
#if WITH_PERIODIC_DEBUG
static struct ctimer debug_timer;
static void
periodic_debug(void *ptr)
{
  ctimer_set(&debug_timer, 20 * CLOCK_SECOND, periodic_debug, NULL);
  collect_print_stats();
}
#endif /* WITH_PERIODIC_DEBUG */
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(sky_shell_process, ev, data)
{
  PROCESS_BEGIN();

#if WITH_PERIODIC_DEBUG
  ctimer_set(&debug_timer, 20 * CLOCK_SECOND, periodic_debug, NULL);
#endif /* WITH_PERIODIC_DEBUG */

  serial_shell_init();
  shell_blink_init();
  shell_reboot_init();
  shell_sky_init();
  shell_power_init();
  shell_powertrace_init();
  shell_text_init();
  shell_time_init();

  shell_collect_view_init();
  shell_math_init();

  
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
