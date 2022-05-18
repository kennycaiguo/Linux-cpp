#ifndef TMP_HPP
#define TMP_HPP
#include<iostream>
#include<initializer_list>
using namespace std;

template<class T>
T getMax(T a,T b)
{
    return a>b?a:b;
}

void testGetMax()
{
    int max=getMax<int>(100,200);
    cout<<"max = "<<max<<endl;
}

template<class T>
T anyMax(initializer_list<T> i)
{
    T tmp;
    for(T t :i)
    {
        if(t>tmp)
        {
            tmp=t;
        }
    }
    return tmp;
}

void testAnyMax()
{
    int max=anyMax<int>({100,200,60,40,50,90});
     cout<<"max = "<<max<<endl;
}
#endif // TMP_HPP
