#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

volatile int counter(0);//全局累加器
mutex mtx;

void thfunc()
{
  for(int i=0;i<10000;i++)
  {
    if(mtx.try_lock())//上锁
	{
	   ++counter;//累加器累加
	   mtx.unlock();//解锁
	}
	else
	{
	 cout<<"try_lock false\n";
	}
  }
}

int main(int argc,char** argv)
{
 thread threads[10];
 for(int i=0;i<10;i++)
 {
   threads[i]=thread(thfunc);//启动10个线程
 }
 
 for(auto &th: threads)
 {
   th.join();//等待10个线程结束
 }
 cout<<"count to "<< counter<<"successfully\n";
 return 0;
}


	

