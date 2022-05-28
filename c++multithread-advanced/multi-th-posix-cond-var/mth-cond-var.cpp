#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;

void* thread1(void* );
void* thread2(void* );

int i=1;
int main(void)
{
  pthread_t t_a;
  pthread_t t_b;
  
  pthread_create(&t_a,NULL,thread2,(void*)NULL);//创建线程t_a
  pthread_create(&t_b,NULL,thread1,(void*)NULL);//创建线程t_b
  pthread_join(t_b,NULL);//等待线程t_b结束
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cond);
  
  exit(0);
}

void* thread1(void* junk)
{
   for(i=1;i<=20;i++)
   {
     pthread_mutex_lock(&mutex);//上锁
	 if(i%3==0)
	 {
	   pthread_cond_signal(&cond);
	 }
	 else
	 {
	   printf("thread1:%d\n",i);
	 }
	 pthread_mutex_unlock(&mutex);//解锁
	 sleep(1);
   }
}

void* thread2(void* junk)
{
  while(i<20)
  {
    pthread_mutex_lock(&mutex);
	if(i%3!=0)
	{
	  pthread_cond_wait(&cond,&mutex);//等待条件变量
	}
	printf("----------------thread2:%d\n",i);//输出能整除3的i
	pthread_mutex_unlock(&mutex);
	
	sleep(1);
	i++;
  }
}

