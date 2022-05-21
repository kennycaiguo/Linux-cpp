#include<pthread.h>
#include<stdio.h>
#include<unistd.h>

void *thfunc(void *arg)
{
   printf("in thfunc\n");
   return (void*)0;
}

int main(int argc,char* argv[])
{
  pthread_t tidp;
  int ret;
  ret=pthread_create(&tidp,NULL,thfunc,NULL);//创建线程
  if(ret)
  {
    printf("pthread_create failed:%d\n",ret);
    return -1;
  }
  sleep(1);//main线程挂起1秒钟，为了让子线程有机会执行
 printf("in main:thread is created\n");
  return 0;
}


