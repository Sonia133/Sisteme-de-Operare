#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int f_mat[3][3] = {{1,2,3} , {4,5,6} , {7,8,9}};
int s_mat[3][3] = {{1,3,5} , {2,4,6} , {2,3,4}};
pthread_t thr[9];
int res[9];

typedef struct mat{
    
    int lin,col;

}mat;

void* elem(void*e){
    
  mat *inds = (mat*)e;
  int *res = malloc(sizeof(int));
  for(int k = 0;k < 3; k++)
    (*res) += f_mat[inds->lin][k]*s_mat[k][inds->col];
   return (void*)(res);
}

int main(){
  
  mat ind[9];
  for(int i = 0;i < 3;i++)
    for(int j = 0;j < 3;j++){
       ind[i*3+j].lin = i;
       ind[i*3+j].col = j;
    }

  for(int i = 0;i < 3;i++)
    for(int j = 0;j < 3;j++){
      if(pthread_create(&thr[i*3+j], NULL, elem, &ind[i*3+j])){
        perror(NULL);
        return errno;
       }
    }

  for(int i = 0;i < 3;i++)
   for(int j = 0;j < 3;j++){
     int *result;
    if(pthread_join(thr[i*3+j], (void **)&result)){
     perror(NULL);
     return errno;
    }
   res[i*3+j] = *result;
   if(result)
   free(result);
  }

  for(int i = 0;i < 3;i++){
   for(int j = 0;j < 3;j++)
    printf("%d ",res[i*3+j]); 
    printf("\n");
  }
       
return 0;
}
