#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int *res;
int **f_mat, **s_mat, n_f, m_f, n_s, m_s;

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

  write(1, "Introduceti dimensiunile primei matrice:\n", 42);
  scanf("%d%d", &n_f, &m_f);
  write(1, "Introduceti dimensiunile celei de-a doua matrice:\n", 51);
  scanf("%d%d", &n_s, &m_s);
  write(1, "Introduceti prima matrice:\n", 28);
  f_mat = (int**)malloc(n_f*sizeof(int));
  for(int i = 0; i < n_f; i++)
   f_mat[i] = (int*)malloc(m_f*sizeof(int));
  for(int i = 0; i < n_f; i++)
   for(int j = 0; j < m_f; j++)
    scanf("%d", &f_mat[i][j]);
  write(1, "Introduceti a doua matrice:\n", 29);
  s_mat = (int**)malloc(n_s*sizeof(int));
  for(int i = 0; i < n_s; i++)
   s_mat[i] = (int*)malloc(m_s*sizeof(int));
  for(int i = 0; i < n_s; i++)
   for(int j = 0; j < m_s; j++)
    scanf("%d", &s_mat[i][j]);
  int elements = n_s*m_f;
  mat ind[elements];
  pthread_t thr[elements];
  res = (int*)malloc(elements*sizeof(int));
  for(int i = 0;i < n_f;i++)
    for(int j = 0;j < m_s;j++){
       ind[i*m_s+j].lin = i;
       ind[i*m_s+j].col = j;
    }


  for(int i = 0;i < n_f;i++)
    for(int j = 0;j < m_s;j++){
      if(pthread_create(&thr[i*m_s+j], NULL, elem, &ind[i*m_s+j])){
        perror(NULL);
        return errno;
       }
    }

  for(int i = 0;i < n_f;i++)
   for(int j = 0;j < m_s;j++){
     int *result;
    if(pthread_join(thr[i*m_s+j], (void **)&result)){
     perror(NULL);
     return errno;
    }
   res[i*m_s+j] = *result;
   if(result)
   free(result);
  }

  for(int i = 0;i < n_f;i++){
   for(int j = 0;j < m_s;j++)
    printf("%d ",res[i*m_s+j]);
    printf("\n");
  }

return 0;
}
