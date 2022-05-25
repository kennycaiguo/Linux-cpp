#include<iostream>
#include<thread>

using namespace std;
thread::id main_thread_id=this_thread::get_id();//获取主线程id

void is_main_thread()
{
  if(main_thread_id==this_thread::get_id())//判断是否和主线程id相同
      cout<<"This is the main thread.\n";
  else
     cout<<"This is not the main thread.\n";   
}

int main()
{
  is_main_thread();//is_main_thread作为main线程的普通函数使用
  thread t(is_main_thread);//is_main_thread作为线程函数使用
  t.join();
  return 0;
}

