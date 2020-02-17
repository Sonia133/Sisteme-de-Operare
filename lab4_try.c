#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

void collatz(int n)
{
   printf("%d : ",n);
   printf("%d ",n);

   while(n!=1)
   { 
       if(n%2==0)
         { 
             printf("%d ",n/2);
             n = n/2;
         }
       else 
        {
             printf("%d ",3*n+1);
             n = 3*n+1;
        }

    }
  printf("\n");
}   

int main(int nargv,char **argv[])
{
if(nargv<2)
   {
     perror("Nr invalid de arg\n");
     return errno;
   }
printf("Starting parrent %d\n", getpid());
for(int i = 1; i < nargv; i++)
{
     pid_t pid;
     pid = fork();
     if(pid < 0)
      return errno;
     if(pid == 0)
   { 
      int n;
      n = atoi(argv[i]); 
      collatz(n);
      printf("Done parent %d Me %d\n", getppid(), getpid());
      exit(0);
   }
}
for(int i = 1; i < nargv; i++)
wait(NULL);

printf("Done parent %d Me %d\n", getppid(), getpid());
return 0;
}
