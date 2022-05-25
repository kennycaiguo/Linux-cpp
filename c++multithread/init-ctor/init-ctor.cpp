//init-constructor
#include<iostream>
#include<thread>
#include<unistd.h>

using namespace std;

void thfunc()
{
 cout<<"i am a c++11 thread func"<<endl;
}


int main(int argc,char** argv)
{
 thread t(thfunc);//定义线程对象，并把线程函数传入
 sleep(1);
 return 0;
}
