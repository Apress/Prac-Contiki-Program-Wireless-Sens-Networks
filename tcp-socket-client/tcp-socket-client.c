#include <stdio.h>
#include "contiki-net.h"
#include "contiki-lib.h"

static struct psock ps;
static uint8_t buffer[100];

PROCESS(tcp_client_process, "TCP Client");
AUTOSTART_PROCESSES(&tcp_client_process);

static int
handle_connection(struct psock *p)
{
  PSOCK_BEGIN(p);

  printf("Receiving messages...\n");

  while(1) {
    PSOCK_READTO(p, '\n');
    printf("RECV: %s", buffer);
  }
  
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

PROCESS_THREAD(tcp_client_process, ev, data)
{
  uip_ipaddr_t addr;

  PROCESS_BEGIN();
  uip_ip6addr(&addr,0xfe80,0,0,0,0x0102,0x0304,0x0506,0x0708);
  tcp_connect(&addr, UIP_HTONS(9061), NULL);

  printf("TCP client started.\n");
  // print_local_addresses();
  printf("Connecting...\n");
  PROCESS_WAIT_EVENT_UNTIL(ev == tcpip_event);

  if(uip_aborted() || uip_timedout() || uip_closed()) {
    printf("Could not establish connection\n");
  } else if(uip_connected()) {
    printf("Connected\n");
    
    PSOCK_INIT(&ps, buffer, sizeof(buffer));

    do {
      handle_connection(&ps);
      PROCESS_WAIT_EVENT_UNTIL(ev == tcpip_event);
    } while(!(uip_closed() || uip_aborted() || uip_timedout()));

    printf("\nConnection closed.\n");
  }
  PROCESS_END();
}
