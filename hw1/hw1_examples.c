int allgood(void){
  return 0;
}


int foo(char *src, int(*fp)(void)){
  char ours[1024];
  strcpy(src, ours);
  return fp();
}


int main(int argc, char *argv[]){
  return foo(argv[1], &allgood);
}
