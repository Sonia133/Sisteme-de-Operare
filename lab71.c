#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <stdio.h>

#define MAX_RESOURCES 5
int available_resources = MAX_RESOURCES;

pthread_mutex_t mtx;
pthread_t thr[5];

void* decrease_count(void* count) {

   int*count1 = (int*) count;
   pthread_mutex_lock(&mtx);
   if(available_resources < *count1)
      printf("Got %d, resources not enough \n", *count1);
   else {
      available_resources -= *count1;
      printf("Got %d resources %d remaining \n", *count1, available_resources);
   }
   pthread_mutex_unlock(&mtx);

  return 0;
}

void* increase_count(void* count) {

    int*count1 = (int*) count;
    pthread_mutex_lock(&mtx);
    available_resources += *count1;
    printf("Released %d resources %d remaining \n", *count1, available_resources);
    pthread_mutex_unlock(&mtx);

    return 0;
}

int main() {

 if (pthread_mutex_init(&mtx, NULL)) {
     perror(NULL);
     return errno;
 }
 for(int i = 0; i < 5; i++) {
   if(i % 2 != 0) {
    int *index= (int*)malloc(sizeof(int));
    *index = i;
    if(pthread_create(&thr[i], NULL, increase_count, index)) {
       perror(NULL);
       return errno;
    }
  }
  else {
  int *index = (int*)malloc(sizeof(int));
  *index = i;
    if(pthread_create(&thr[i], NULL, decrease_count, index)) {
      perror(NULL);
      return errno;
    }
  }
 }


 for(int i = 0; i < 5; i++) {
  int* res;
  if(pthread_join(thr[i], (void**)&res)) {
    perror(NULL);
    return errno;
  }
 }

pthread_mutex_destroy(&mtx);
return 0;
}

