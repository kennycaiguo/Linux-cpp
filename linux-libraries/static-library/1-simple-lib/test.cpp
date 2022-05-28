extern void f(int age);//声明要使用的函数
#include<iostream>
using namespace std;

int main(void)
{
  f(100);
  cout<<"function call to lib done"<<endl;
  return 0;
}
