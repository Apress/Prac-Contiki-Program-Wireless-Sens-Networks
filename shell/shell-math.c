#include "contiki.h"
#include "shell.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

/*---------------------------------------------------------------------------*/
PROCESS(shell_math_process, "math");
SHELL_COMMAND(math_command,
	      "math",
	      "math: math number1 number2",
	      &shell_math_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(shell_math_process, ev, data)
{
  char *numbers;
  int n1 = 0;
  int n2 = 0;
  char buf[32];

  PROCESS_BEGIN();

  numbers = data;
  if(numbers == NULL || strlen(numbers) == 0) {
    shell_output_str(&math_command,
		     "math number1 number2: number must be given", "");
    PROCESS_EXIT();
  }

  char * pch;
  pch = strtok (numbers," ");
  if (pch != NULL)
  {      
      n1 = atoi(pch);
      pch = strtok (NULL, " ");
      if (pch != NULL)
      {      
          n2 = atoi(pch);         
      }else
      {
        shell_output_str(&math_command,
          "math number1 number2: number must be given", "");
      PROCESS_EXIT();
      }
  }else
  {
    shell_output_str(&math_command,
      "math number1 number2: number must be given", "");
    PROCESS_EXIT();
  }
  int s = n1 + n2;
  sprintf(buf, "%d + %d= %d", n1, n2, s);
  
  shell_output_str(&math_command, buf, "");
  
  PROCESS_END();
}

/*---------------------------------------------------------------------------*/
void
shell_math_init(void)
{
  shell_register_command(&math_command);
}
/*---------------------------------------------------------------------------*/