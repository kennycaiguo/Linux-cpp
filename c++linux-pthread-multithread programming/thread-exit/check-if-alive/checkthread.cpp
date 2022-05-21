#include<iostream>
#include<pthread.h>
#include<signal.h>
#include<unistd.h>
#include<errno.h>
using namespace std;

void *thfunc(void* arg)
{
 int tm=50;
 while(1)
 {
  cout<<"thfunc--left:"<<tm<<" s--"<<endl;
  sleep(1);
  tm--;
 } 
 return (void*)0;
}

int main(int argc,char* argv[])
{
 pthread_t pid;
 int res;
 
 res=pthread_create(&pid,NULL,thfunc,NULL);
 sleep(5);
 int killrc = pthread_kill(pid,0);//发送0信号，探测线程是否活着
 if(killrc==ESRCH)
 {
   cout<<"thread no exists or already quit\n";
   
 }
 else if(killrc==EINVAL)
 {
   cout<<"signal is invalid\n";
 }
 else
 {
   cout<<"the specified thread is alive\n";
 }
 return 0;
}

