//取消线程成功
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

void* thfunc(void* arg)
{
 int i=1;
 printf("thread start----------------------\n");
 while(1)
 {
  i++;
  pthread_testcancel();//让系统测试取消请求
 }
 return (void*)0;
}

int main()
{
  void *ret = NULL;
  int iret= 0;
  pthread_t tid;
  pthread_create(&tid,NULL,thfunc,NULL);//创建线程
  sleep(1);
  
  pthread_cancel(tid);//发送取消线程的请求
  pthread_join(tid,&ret);//等待线程结束
  if(ret==PTHREAD_CANCELED)
    printf("thread has stopped,and exit code:%d\n",ret);
  else
    printf("some error occured\n");
	
  return 0;
}
