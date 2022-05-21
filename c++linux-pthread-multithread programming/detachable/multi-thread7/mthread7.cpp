#include<pthread.h>
#include<iostream>
#include<unistd.h>

using namespace std;

void *thfunc(void* arg)
{
  
  cout<<"sub thread is running\n";//输出字符串
  return NULL;
   
}

int main(int argc,char* argv[])
{
  pthread_t thread_id;
  int res;
  pthread_attr_t thread_attr;
  struct sched_param thread_param;
  size_t stack_size;
  //初始化thread_attr
  res=pthread_attr_init(&thread_attr);
  if(res)
  {
    cout<<"pthread_attr_init failed:"<<res<<endl;
	
  }
  //设置可分离状态
  res=pthread_attr_setdetachstate(&thread_attr,PTHREAD_CREATE_DETACHED);
   if(res)
  {
    cout<<"pthread_attr_setdetachstate failed:"<<res<<endl;
	
  }
  
  res=pthread_create(&thread_id,&thread_attr,thfunc,NULL);//创可分离建子线程
  if(res)
  {
     cout<<"pthread_create failed:"<<res<<endl;
     //return -1;
  }
  cout<<"main thread will exit"<<endl;
  pthread_exit(NULL);//主线程退出，但是进程不会此刻退出。注意：自由在主线程main调用该函数才有这样的效果，在子线程中调用，只会导致该子线程退出而已
  return 0;
}

