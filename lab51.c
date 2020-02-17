#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

int main(int nargv,char **argv){
if(nargv<2) {
     perror("Nr invalid de arg\n");
     return errno;
   }
int n;
char shm_name[] = "myshm";
int shm_fd;
int counter;
shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
if(shm_fd < 0){
   perror("Eroare");
   return errno;
}
size_t shm_size = (nargv-1)*getpagesize();
if(ftruncate(shm_fd, shm_size) == -1){
  perror("Eroare");
  shm_unlink(shm_name);
  return errno;
}
printf("Starting parent %d\n",getpid());
for(int i = 1; i < nargv; i++)
{
     counter = 1;
     pid_t pid;
     pid = fork();
     if(pid < 0)
      return errno;
     if(pid == 0){
      n = atoi(argv[i]);
      int *shm_ptr = mmap(0, getpagesize(), PROT_WRITE, MAP_SHARED, shm_fd,
(i-1)*getpagesize());
      if(shm_ptr == MAP_FAILED){
         perror("Eroare");
         shm_unlink(shm_name);
         return errno;
      }
      shm_ptr[counter++] = n;
      while(n != 1){
        if(n%2==0)
         {
             n = n/2;
             shm_ptr[counter++] = n;
         }
       else
        {
             n = 3*n+1;
             shm_ptr[counter++] = n;
        }

      }
      shm_ptr[0] = counter - 1;
      printf("Done parent %d Me %d\n",getppid(),getpid());
      exit(0);
   }
}
for(int i = 1;i < nargv; i++)
wait(NULL);

int *shm_ptr = mmap(0, shm_size, PROT_READ, MAP_SHARED, shm_fd, 0);
for(int i = 0; i < nargv-1; i++){
  int *p = &shm_ptr[i*getpagesize()/sizeof(int)];
  int sz_p = p[0];
  printf("%d : ", p[1]);
  for(int j = 1; j <= sz_p; j++){
  printf(" %d ", p[j]);
  }
  printf("\n");
}

printf("Done parent %d Me %d\n",getppid(),getpid());

munmap(shm_ptr, shm_size);
shm_unlink(shm_name);

return 0;
}
