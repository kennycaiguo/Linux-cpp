//线程赛跑
#include<iostream>
#include<thread>
#include<atomic>
using namespace std;

atomic<bool> ready(false);//定义全局变量


void thfunc(int id)
{
  while(!ready) //一直等待，直到main线程中重置变量ready
     this_thread::yield();//让出自己的CPU时间片
  for(volatile int i=0;i<1000000;++i){} //1+..+1000000
  cout<<id<<", ";
}

int main()
{
  thread threads[10];//定义10个线程对象
  cout<<"race of 10 threads that count to 1 million:\n";
  for(int i=0;i<10;i++)
     threads[i]=thread(thfunc,i); //启动线程，i用于标记线程的序号
  ready=true;//重置ready的值	 
  for(auto& th : threads)
     th.join();//等待10个线程结束
  cout<<"\n";

  return 0;  
}

