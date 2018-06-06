
#include "contiki.h"
#include "rpl.h"
#include "httpd-simple.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Log configuration */
#include "sys/log.h"
#define LOG_MODULE "Web Sense DB"
#define LOG_LEVEL LOG_LEVEL_INFO


/*---------------------------------------------------------------------------*/
static
PT_THREAD(generate_routes(struct httpd_state *s))
{
  char buff[35];

  PSOCK_BEGIN(&s->sout);
  //SEND_STRING(&s->sout, TOP);

  int temperature = 15 + rand() % 25;
  int humidity = 80 + rand() % 10;

  sprintf(buff,"{\"temp\":%u,\"hum\":%u}", temperature, humidity);
  printf("send json to requester\n");

  SEND_STRING(&s->sout, buff);
  //SEND_STRING(&s->sout, BOTTOM);

  PSOCK_END(&s->sout);
}
/*---------------------------------------------------------------------------*/
PROCESS(webserver_nogui_process, "Web Sense-db server");
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
PROCESS(web_sense_db, "Web Sense-db");
AUTOSTART_PROCESSES(&web_sense_db);

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(web_sense_db, ev, data)
{
  PROCESS_BEGIN();

  PROCESS_NAME(webserver_nogui_process);
  process_start(&webserver_nogui_process, NULL);

  LOG_INFO("Web Sense started\n");

  PROCESS_END();
}