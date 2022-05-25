//c++和posix将可连接线程变为可分离线程
#include<iostream>
#include<thread>
#include<pthread.h>

using namespace std;

void thfunc(int n,int m,int* pk,char s[])
{
 cout<<"thfunc:n="<< n<<",m="<<m<<",k="<<*pk<<",s="<<s<<endl;
 *pk=5000;
}

int main(void)
{
  int n=100,m=200,k=100;
   char s[]="hello sexy";
   thread t(thfunc,n,m,&k,s);
   //分离线程
   t.detach();
   cout<<"k="<<k<<endl;
   pthread_exit(NULL);//main线程结束，但是进程并不会结束，下面这一句不会执行
   cout<<"this line will not print"<<endl;
   return 0;
   
}

