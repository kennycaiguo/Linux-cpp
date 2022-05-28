//多线程卖货例子
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

int a=200; //当前货物价值
int b=100; //当前现金

pthread_mutex_t lock;

void* ThreadA(void*)//伙计卖货线程
{
   while(1)
   {
     pthread_mutex_lock(&lock);//上锁
	 a-=50;//卖出价值50元的货物
	 b+=50;//收回50元现金
	 pthread_mutex_unlock(&lock);//解锁
   }
}

void* ThreadB(void*)//老板对账线程
{
   while(1)
   {
     pthread_mutex_lock(&lock);//上锁
	 printf("total=%d\n",a+b);
	 pthread_mutex_unlock(&lock);//解锁
	 sleep(1);
   }
}

int main()
{
  pthread_t tida,tidb;
  pthread_mutex_init(&lock,NULL);//初始化互斥锁
  pthread_create(&tida,NULL,ThreadA,NULL);//创建伙计卖货线程
  pthread_create(&tidb,NULL,ThreadB,NULL);//创建老板对账线程
  
  pthread_join(tida,NULL);
  pthread_join(tidb,NULL);
  
  pthread_mutex_destroy(&lock);
  
  return 1;
}
