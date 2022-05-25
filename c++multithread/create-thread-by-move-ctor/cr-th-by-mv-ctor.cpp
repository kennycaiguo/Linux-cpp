//通过移动构造函数来启动线程
#include<iostream>
#include<thread>
#include<chrono>
using namespace std;

void fun(int& n)
{
 cout<<"fun:"<<n<<endl;
 n+=20;
 this_thread::sleep_for(chrono::milliseconds(10));//等待10秒
 
}

int main()
{
  int n=0;
  cout<<"n="<<n<<"\n";
  n=10;
  thread t1(fun,ref(n));//ref(n)是去n的引用
  thread t2(move(t1));//t2 执行fun，t1不是thread对象
  t2.join();//等待t2执行完毕
  cout<<"n="<<n<<"\n";
  return 0;
}

//注意：t1并不会执行，因为它移动给了t2
