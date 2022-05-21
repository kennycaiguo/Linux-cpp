#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>

void cleanupfunc(void* arg)
{
 printf("cleanupfunc:%d\n",*((int*)arg));//输出传递进来的参数
}
void* thfunc1(void* arg)
{
  int m=1;
  printf("thread start---------------------\n");
  pthread_cleanup_push(cleanupfunc,&m);//把清理函数压栈
  
 while(1)
 {
   m++;
   printf("m=%d\n",m);
 }
 printf("this will not run");//这句话不会执行
 pthread_cleanup_pop(0);//这一句不会执行，但是不能少，否则编译不通过
 return (void*)0;
}


int main(void)
{
  pthread_t pid1;
  void* ret = NULL;
  
  pthread_create(&pid1,NULL,thfunc1,NULL);
  sleep(1);
  pthread_cancel(pid1);//发送取消线程的请求
  pthread_join(pid1,&ret);//等待线程结束
  if(ret==PTHREAD_CANCELED)
     printf("thread has stopped,and exit code:%d\n",ret);
  else
     printf("some error occured\n");   
  printf("main is over\n");
  return 0;
}
