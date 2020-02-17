#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc,char**arg)
{
   if(argc < 3)
    {
       perror("Nr arg invalid\n");
       return errno;
    }
    int f,cp,nread,nwrite,tw=0;
    char s[512];
    f = open(arg[1],O_RDONLY);
    if(f < 0)
    {
       perror("Eroare la citire\n");
       return errno;
    }
    cp = open(arg[2],O_RDWR | O_CREAT, 644);
    if(cp < 0)
    {
       perror("Eroare la scriere\n");
       return errno;
    }
    while((nread=read(f,s,512)) > 0)
     {
       tw = 0;
       while((nwrite=write(cp,s+tw,nread-tw)) > 0)
         tw += nwrite;
       memset(s,0,512);
     }
return 0;
}


