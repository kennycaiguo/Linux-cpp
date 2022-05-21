#include<pthread.h>
#include<stdio.h>
int gn=10;
void *thfunc(void* arg)
{
   gn++;//接收传递进来的字符串
  printf("in thfunc:gn=%d",gn);//输出字符串
  return (void*)0;
   
}

int main(int argc,char* argv[])
{
  pthread_t tidp;
  int ret;

  ret=pthread_create(&tidp,NULL,thfunc,NULL);
  if(ret)
  {
     printf("pthread_create failed:%d\n",ret);
     return -1;
  }
  pthread_join(tidp,NULL);
  gn++;
  printf("in main:gn=%d\n",gn);
  return 0;
}

