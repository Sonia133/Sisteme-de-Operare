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
     int n;
     pid_t pid=fork();
     if(pid<0)
       return errno;
      else if(pid == 0)
         {
           n = atoi(argv[1]);
           collatz(n);
         }
      else
         {
               wait(NULL);
               printf("Child %d finished\n", pid);
         }
    return 0;
}

