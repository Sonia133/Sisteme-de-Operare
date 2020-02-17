#include<stdio.h>

void small(int n)
{
  n++;
  printf("%d",n);
}

int main()
{
  int n;
  scanf("%d",&n);
  for(int i=0;i<n;i++)
  printf("%d",i+1);
  small(n);
  return 0;
}
