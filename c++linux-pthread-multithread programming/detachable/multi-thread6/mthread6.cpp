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
  sleep(1);
  return 0;
}
