#include "contiki.h"
#include "cfs/cfs.h"
#include "cfs/cfs-coffee.h"
#include "lib/crc16.h"
#include "lib/random.h"

#include <stdio.h>
#include <string.h>
/*---------------------------------------------------------------------------*/
PROCESS(coffee_demo_process, "CFS/Coffee demo process");
AUTOSTART_PROCESSES(&coffee_demo_process);
/*---------------------------------------------------------------------------*/
static void
coffee_file_demo(void)
{
  int wfd, rfd, afd;
  unsigned char buf[32];
  int r;

  wfd = rfd = afd = -1;

  for(r = 0; r < sizeof(buf); r++) {
    buf[r] = r + 4;
  }

  // create and open file
  printf("opening file for writing\n");
  wfd = cfs_open("mycfs", CFS_WRITE);
  if(wfd < 0) {
    printf("Error creating file\n");
    return;
  }

  // write data
  printf("writing data into file\n");
  // print data
  printf("write: ");
  for(r = 0; r < sizeof(buf); r++) {
    printf("%d ", buf[r]);
  }
  printf("\n");
  r = cfs_write(wfd, buf, sizeof(buf));
  if(r < 0) {
    printf("Error writing data into file\n");
    cfs_close(wfd);
    cfs_remove("mycfs");
    return;
  } else if(r < sizeof(buf)) {
    printf("Error writing data into file\n");
    cfs_close(wfd);
    cfs_remove("mycfs");
    return;
  }

  // close file
  printf("close file\n");
  cfs_close(wfd);

  // open and read data from file
  printf("opening file for reading\n");
  rfd = cfs_open("mycfs", CFS_READ);
  if(rfd < 0) {
    printf("Error opening file\n");
    cfs_remove("mycfs");
    return;
  }

  // read data
  printf("reading data\n");
  memset(buf, 0, sizeof(buf));
  r = cfs_read(rfd, buf, sizeof(buf));
  if(r < 0) {
    printf("Error reading file\n");
    cfs_close(rfd);
    cfs_remove("mycfs");
    return;
  }

  // print data
  printf("read: ");
  for(r = 0; r < sizeof(buf); r++) {
    printf("%d ", buf[r]);
  }
  printf("\n");

  printf("close file\n");
  cfs_close(rfd);

  // delete file
  printf("remove file\n");
  cfs_remove("mycfs");
}
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(coffee_demo_process, ev, data)
{
  PROCESS_BEGIN();

  printf("Coffee file demo...\n");
  coffee_file_demo();


  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
