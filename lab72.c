#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <semaphore.h>

pthread_t thr[10];
pthread_mutex_t mtx;
sem_t sem;
int n;
int counter = 0;

int barrier_point() {

  pthread_mutex_lock(&mtx);
  counter++;
  if(counter == n) {
   if(sem_post(&sem)) {
     perror(NULL);
     return errno;
   }
  }
  pthread_mutex_unlock(&mtx);
  if(sem_wait(&sem)) {
    perror(NULL);
    return errno;
  }
  if(sem_post(&sem)) {
    perror(NULL);
    return errno;
  }

}

void* tfun(void *v) {

  int *tid = (int*)v;
  printf("%d reached the barier\n", *tid);
  barrier_point();
  printf("%d passed the barrier\n", *tid);

  free(tid);
  return NULL;
}


int main(int nargv, char**argv) {

 if(nargv < 2) {
  perror("nr invalid de argumente");
  return errno;
 }

 n = atoi(argv[1]);

 if(pthread_mutex_init(&mtx, NULL)) {
   perror(NULL);
   return errno;
 }

 if(sem_init(&sem, 0, counter)) {
   perror(NULL);
   return errno;
 }

 for(int i = 0; i < n; i++) {
  int *ind = (int*)malloc(sizeof(int));
  *ind = i;
  if(pthread_create(&thr[i], NULL, tfun, ind)) {
    perror(NULL);
    return errno;
  }
 }

 for(int i = 0; i < n; i++) {
  int *res;
  if(pthread_join(thr[i], (void**)&res)) {
    perror(NULL);
    return errno;
  }
 }

 pthread_mutex_destroy(&mtx);
 sem_destroy(&sem);
 return 0;
}
