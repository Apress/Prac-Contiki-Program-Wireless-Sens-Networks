#include <string.h>
#include <stdio.h>
#include "contiki-net.h"


static struct psock ps;
static uint8_t buffer[10];

static
PT_THREAD(handle_connection(struct psock *p))
{
  PSOCK_BEGIN(p);

  PSOCK_SEND_STR(p, "Connection accepted. Echo\r\n");    
  
  PSOCK_CLOSE(p);
  PSOCK_END(p);
}

// static void
// print_local_addresses(void)
// {
//   int i;
//   uip_netif_state state;

//   PRINTF("Local IPv6 addresses: ");
//   for(i = 0; i < UIP_CONF_NETIF_MAX_ADDRESSES; i++) {
//      state = uip_netif_physical_if.addresses[i].state;
//      if(state == TENTATIVE || state == PREFERRED) {
//         PRINT6ADDR(&uip_netif_physical_if.addresses[i].ipaddr);
//         PRINTF("\n");
//      }
//   }
// }

PROCESS(tcp_server_process, "TCP server");
AUTOSTART_PROCESSES(&tcp_server_process);

PROCESS_THREAD(tcp_server_process, ev, data)
{

  PROCESS_BEGIN();
  printf("TCP Server sarted\n");
  // print_local_addresses();
  printf("Listening client...\n");
  tcp_listen(UIP_HTONS(9061));

  while(1) {

    PROCESS_WAIT_EVENT_UNTIL(ev == tcpip_event);
    if(uip_connected()) {
      
      PSOCK_INIT(&ps, buffer, sizeof(buffer));
      while(!(uip_aborted() || uip_closed() || uip_timedout())) {

	      PROCESS_WAIT_EVENT_UNTIL(ev == tcpip_event);
        printf("Accepted client.\n");        
	      handle_connection(&ps);
      }
    }
  }  
  PROCESS_END();
}