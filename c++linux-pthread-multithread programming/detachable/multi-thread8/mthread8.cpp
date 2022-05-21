#ifndef _GNU_SOURCE
#define _GNU_SOURCE //为了能够使用pthread_getattr_np()函数
#endif
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>

//#define handle_error_en(en,msg)\ //输出自定义错误信息
        //do{errno = en;perror(msg);exit(EXIT_FAILURE);} while(0)

void handle_error_en(int en,char* msg)
{
   do{
      errno = en;
      perror(msg);
      exit(EXIT_FAILURE);
     } while(0);
}

static void *thread_start(void* arg)
{
 int i,s;
 pthread_attr_t gattr;//定义线程属性联合体
 s= pthread_getattr_np(pthread_self(),&gattr);//获取当前线程属性
 if(s!=0)
 {
  handle_error_en(s,"pthread_getattr_np");//输出错误信息
 } 
 printf("Thread's detachstate attributes:\n"); 
 s = pthread_attr_getdetachstate(&gattr,&i);//获取分离状态属性
 if(s)
 {
   handle_error_en(s,"pthread_attr_getdetachstate");
 }
 printf("Detach state = %s\n",
        (i==PTHREAD_CREATE_DETACHED)?"PTHREAD_CREATE_DETACHED":
        (i==PTHREAD_CREATE_JOINABLE)?"PTHREAD_CREATE_JOINABLE":
		"???");
  pthread_attr_destroy(&gattr);		
}

int main()
{
   pthread_t thr;
   int s;
   s=pthread_create(&thr,NULL,&thread_start,NULL);
   if(s!=0)
   {
     handle_error_en(s,"pthread_create");
	 return 0;
   } 
  pthread_join(thr,NULL);//等待子线程结束
  return 0;
}
