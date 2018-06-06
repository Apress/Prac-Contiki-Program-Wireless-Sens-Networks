
#include "contiki.h"
#include "rpl.h"
#include "httpd-simple.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Log configuration */
#include "sys/log.h"
#define LOG_MODULE "Web Sense"
#define LOG_LEVEL LOG_LEVEL_INFO


/*---------------------------------------------------------------------------*/
static
PT_THREAD(generate_routes(struct httpd_state *s))
{
  char buff[15];

  PSOCK_BEGIN(&s->sout);


  int temperature = 15 + rand() % 25;

  sprintf(buff,"{\"temp\":%u}", temperature);
  printf("send json to requester\n");

  SEND_STRING(&s->sout, buff);

  PSOCK_END(&s->sout);
}
/*---------------------------------------------------------------------------*/
PROCESS(webserver_nogui_process, "Web Sense server");
PROCESS_THREAD(webserver_nogui_process, ev, data)
{
  PROCESS_BEGIN();

  httpd_init();

  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(ev == tcpip_event);
    httpd_appcall(data);
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
httpd_simple_script_t
httpd_simple_get_script(const char *name)
{
  return generate_routes;
}
/*---------------------------------------------------------------------------*/
/* Declare and auto-start this file's process */
PROCESS(web_sense, "Web Sense");
AUTOSTART_PROCESSES(&web_sense);

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(web_sense, ev, data)
{
  PROCESS_BEGIN();

  PROCESS_NAME(webserver_nogui_process);
  process_start(&webserver_nogui_process, NULL);

  LOG_INFO("Web Sense started\n");

  PROCESS_END();
}