#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void*
reverse(void *s){

  char*s1 = (char*)s;
  char*rev = malloc(strlen(s1)*sizeof(char));
  for(int i = 0;i < strlen(s1); i++)
    rev[strlen(s1)-i-1] = s1[i];
  return (void*)rev;
}

int main(int nargv, char** argv){

  if(nargv < 2){
    perror("Numar invalid de argumente!");
    return errno;
  }
  pthread_t thr;
 if(pthread_create(&thr, NULL, reverse, argv[1])){
    perror(NULL);
    return errno;
  }

char *res;
if(pthread_join(thr, (void **)&res)){
  perror(NULL);
  return errno;
}
else printf("%s\n", res);

return 0;
}
