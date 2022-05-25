//创建一个线程并且传入整型参数
#include<iostream>
#include<thread>

using namespace std;

void thfunc(int n)
{
 cout<<"thfunc:"<< n <<endl;
}

int main(int argc,char** argv)
{
   thread t(thfunc,1);
   t.join();
   return 0;
}

