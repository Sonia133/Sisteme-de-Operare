#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

  
  int main()
{
     int pred=0,succ=0,n=5;
     pid_t pid=fork();
     if(pid<0)
       return errno;
      else if(pid == 0)
         {
            pred = n-1;
            char*argv[]={"ls",NULL};
            //printf("%s %d\n","Copil ",pred);
            execve("/bin/ls",argv,NULL);
            perror(NULL);
         }
      else
         {
            succ = n+1;
            //printf("%s %d\n","Parinte ",succ);
            printf("My PID %d Child PID %d \n", getpid(), pid);
            printf("Child %d finished\n",wait(NULL));
         }
   
 return 0;    
}
