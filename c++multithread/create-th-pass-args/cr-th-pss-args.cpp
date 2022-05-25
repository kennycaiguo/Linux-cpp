//创建一个线程并且传入整型参数
#include<iostream>
#include<thread>

using namespace std;

void thfunc(int n,int m,int* pk,char s[])
{
 cout<<"thfunc:n="<< n<<",m="<<m<<",k="<<*pk<<",s="<<s<<endl;
 *pk=5000;
}

int main(int argc,char** argv)
{
    int n=100,m=200,k=100;
   char s[]="hello sexy";
   thread t(thfunc,n,m,&k,s);
   t.join();
   cout<<"k = "<<k<<endl;
   return 0;
}

