#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>

void cleanupfunc(void* arg)
{
 printf("cleanupfunc:%d\n",*((int*)arg));//输出传递进来的参数
}
void* thfunc1(void* arg)
{
  int m=1;
  printf("thfunc1 comes \n");
  pthread_cleanup_push(cleanupfunc,&m);//把清理函数压栈
  return (void*)0; //退出线程
  pthread_cleanup_pop(0);//这一句不会执行，但是不能少，否则编译不通过
}

void* thfunc2(void* arg)
{
  int m=2;
  printf("thfunc2 comes \n");
  pthread_cleanup_push(cleanupfunc,&m);//把清理函数压栈
  pthread_exit(0); //退出线程
  pthread_cleanup_pop(0);//这一句不会执行，但是不能少，否则编译不通过
}

int main(void)
{
  pthread_t pid1,pid2;
  int res;
  res = pthread_create(&pid1,NULL,thfunc1,NULL);
  if(res)
  {
    printf("pthread_create failed:%d\n",strerror(res));
	exit(0);
  }
  pthread_join(pid1,NULL);//等待线程1结束
  
   res = pthread_create(&pid2,NULL,thfunc2,NULL);
  if(res)
  {
    printf("pthread_create failed:%d\n",strerror(res));
	exit(0);
  }
  pthread_join(pid2,NULL);//等待线程2结束
  printf("main is over\n");
  return 0;
}
