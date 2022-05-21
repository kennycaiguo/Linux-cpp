#include<pthread.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>

#define PTHREAD_NUM 2

void *thrfunc1(void* arg)
{
  static int count=1;
  pthread_exit((void*)(&count));//通过pthread_exit结束线程
}

void *thrfunc2(void* arg)
{
  static int count=2;
  return (void*)(&count);//线程函数返回
}

int main(int argc,char* argv[])
{
   pthread_t pid[PTHREAD_NUM]; //定义两个线程id
   int retPid;
   int* pret1,*pret2; //注意这里是指针
   
   //创建的一个线程
   if((retPid=pthread_create(&pid[0],NULL,thrfunc1,NULL))!=0)
   {
    perror("created pid first failed\n");
	return -1;
   }
   if((retPid=pthread_create(&pid[1],NULL,thrfunc2,NULL))!=0)
   {
    perror("created pid second failed\n");
	return -1;
   }
   if(pid[0]!=0)
   {
      pthread_join(pid[0],(void**) &pret1);//注意pthread_join第二个参数的用法
	  printf("get thread 0 exitcode:%d\n",*pret1);//输出线程返回值
   }
   if(pid[1]!=0)
   {
      pthread_join(pid[1],(void**) &pret2);//注意pthread_join第二个参数的用法
	  printf("get thread 1 exitcode:%d\n",*pret2);//输出线程返回值
   }
   return 0;
}

