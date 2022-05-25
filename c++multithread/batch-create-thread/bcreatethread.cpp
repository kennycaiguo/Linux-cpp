#include<stdio.h>
#include<stdlib.h>
#include<chrono>
#include<iostream>
#include<thread>

using namespace std;

void thfunc(int n)
{
 cout<<"thfunc:"<< n <<endl;
}

int main(int argc,char** argv)
{
   thread threads[5];
   cout<<"create 5 threads...\n";
   for(int i=0;i<5;i++)
   {
     threads[i] = thread(thfunc,i+1);//这里开始执行线程函数thfunc
   }
   
   for(auto& t : threads)
   {
     t.join();//等待每个线程结束
   }   
   cout<<"All threads joined.\n";
   return EXIT_SUCCESS;
}

