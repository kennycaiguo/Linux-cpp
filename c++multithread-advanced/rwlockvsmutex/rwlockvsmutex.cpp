//互斥锁和读写锁速度大PK
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/time.h>
#include<string.h>
#include<cstdlib>

int gcn = 0;
pthread_mutex_t mutex;
pthread_rwlock_t rwlock;

void* thread_1(void* arg)
{
 int j;
 volatile int a;
 for(j=0;j<10000000;j++)
 {
   pthread_mutex_lock(&mutex);
   a=gcn;
   pthread_mutex_unlock(&mutex);
 }
  pthread_exit((void*)0);
}

void* thread_2(void* arg)
{
 int j;
  volatile int b;
 for(j=0;j<10000000;j++)
 {
   pthread_mutex_lock(&mutex);
   b=gcn;
   pthread_mutex_unlock(&mutex);
 }
  pthread_exit((void*)0);
}

void* thread_3(void* arg)
{
 int j;
 volatile int a;
 for(j=0;j<10000000;j++)
 {
   pthread_rwlock_rdlock(&rwlock);
   a=gcn;
   pthread_rwlock_unlock(&rwlock);
 }
  pthread_exit((void*)0);
}

void* thread_4(void* arg)
{
 int j;
 volatile int b;
 for(j=0;j<10000000;j++)
 {
   pthread_rwlock_rdlock(&rwlock);
   b=gcn;
   pthread_rwlock_unlock(&rwlock);
 }
  pthread_exit((void*)0);
}

int mutexVer(void)
{
  int j,err;
  pthread_t th1,th2;
  
  struct timeval start;
  clock_t t1,t2;
  struct timeval end;
  
  pthread_mutex_init(&mutex,NULL);//初始化互斥锁
  gettimeofday(&start,NULL);//获取开始时间
  
  err=pthread_create(&th1,NULL,thread_1,(void*)0);
  if(err!=0)
  {
    printf("pthread_create with error:%s\n",strerror(err));
	exit(0);
  }
   err=pthread_create(&th2,NULL,thread_2,(void*)0);
  if(err!=0)
  {
    printf("pthread_create with error:%s\n",strerror(err));
	exit(0);
  }
  err=pthread_join(th1,NULL);
  if(err!=0)
  {
    printf("pthread_join with error:%s\n",strerror(err));
	exit(1);
  }
   err=pthread_join(th2,NULL);
  if(err!=0)
  {
    printf("pthread_join with error:%s\n",strerror(err));
	exit(1);
  }
  gettimeofday(&end,NULL);//获取结束时间
  pthread_mutex_destroy(&mutex);//销毁互斥锁
  long long totaltime=(end.tv_sec - start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);
  totaltime /=1000;
  printf("total mutex time is %lld ms\n",totaltime);
  return 0;
}

int rdlockVer(void)
{
  int j,err;
  pthread_t th3,th4;
  
  struct timeval start;
  clock_t t1,t2;
  struct timeval end;
  
  pthread_rwlock_init(&rwlock,NULL);//初始化互斥锁
  gettimeofday(&start,NULL);//获取开始时间
  
  err=pthread_create(&th3,NULL,thread_3,(void*)0);
  if(err!=0)
  {
    printf("pthread_create with error:%s\n",strerror(err));
	exit(0);
  }
   err=pthread_create(&th4,NULL,thread_4,(void*)0);
  if(err!=0)
  {
    printf("pthread_create with error:%s\n",strerror(err));
	exit(0);
  }
  err=pthread_join(th3,NULL);
  if(err!=0)
  {
    printf("pthread_join with error:%s\n",strerror(err));
	exit(1);
  }
   err=pthread_join(th4,NULL);
  if(err!=0)
  {
    printf("pthread_join with error:%s\n",strerror(err));
	exit(1);
  }
  gettimeofday(&end,NULL);//获取结束时间
  pthread_rwlock_destroy(&rwlock);//销毁读写锁
  long long totaltime=(end.tv_sec - start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);
  totaltime /=1000;
  printf("total rwlock time is %lld ms\n",totaltime);
  return 0;
}

int main()
{
  mutexVer();
  rdlockVer();
  
  return 0;
}
