#ifndef FUNPTR_HPP
#define FUNPTR_HPP
#include<iostream>
using namespace std;

int add(int a,int b)
{
    return a+b;
}

int sub(int a,int b)
{
    return a-b;
}

void numOps(int x,int y,int(*fun)(int a,int b))
{
    cout<<"result="<<fun(x,y)<<endl;
}
#endif // FUNPTR_HPP
