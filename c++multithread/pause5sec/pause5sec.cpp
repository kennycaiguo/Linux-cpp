//让线程暂停5秒钟
#include<iostream>
#include<thread>
#include<chrono>

using namespace std;

int main()
{
 cout<<"countdown:\n";
 for(int i=5;i>0;i--)
 {
   cout<<i<<endl;
   this_thread::sleep_for(chrono::seconds(1));//暂停一秒
 }
 cout<<"Lift off\n";
 return 0;
}
