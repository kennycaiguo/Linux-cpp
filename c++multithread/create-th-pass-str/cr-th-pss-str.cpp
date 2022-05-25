//创建一个线程并且传入整型参数
#include<iostream>
#include<thread>

using namespace std;

void thfunc(char* str)
{
 cout<<"thfunc:"<< str <<endl;
}

int main(int argc,char** argv)
{
   char s[]="hello sexy";
   thread t(thfunc,s);
   t.join();
   return 0;
}

