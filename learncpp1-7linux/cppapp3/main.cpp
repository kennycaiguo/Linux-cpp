#include <iostream>
#include<vector>
#include<string>
#include<string.h>
#include<sstream>
#include"person.h"
#include"funptr.hpp"
#include"rectangle.h"

using namespace std;

void testPerson()
{
    Person p1("lili",18);
    Person p2;
    Person p3("mike",20);
    cout<<p1;
    cout<<p3;
    cout<<"before assignment,p2:\n";
    cout<<p2<<endl;
    p2=p1;
    cout<<"after assignment,p2:\n";
    cout<<p2<<endl;
    cout.setf(ios_base::boolalpha);
    cout<<"lili is older than mike?:"<<(p1>p3)<<endl;
    cout<<"==========================\n";
    cout<<"before change name,p1==p2?"<<(p1==p2)<<endl;
    p2.name="jackline";
    cout<<"after change name,p1==p2?"<<(p1==p2)<<endl;
}

void sstreamTest()
{
    string numstr("1024");
    int num;
    stringstream(numstr)>>num;
    cout<<"num="<<num<<endl;
}
void sstreamTest2()
{
    string numstr("1024 2048 3096");
    int num,num2,num3;
    stringstream(numstr)>>num>>num2>>num3;//可以连续输入
    cout<<"num="<<num<<",num2="<<num2<<",num3="<<num3<<endl;
}

auto lamfun=[](string name,int age){
    cout<<"name:"<<name<<",age:"<<age<<endl;
};

//递归调用
int factorial(int n)
{
    if(n>1)
   {
        return (n*factorial(n-1));
   }
   else
  {
    return 1;
  }
}

void pointerTest()
{
    int num[5];
    int* p;
    p=num;
    *p=10;
    p++;
    *p=20;
    p=&num[2];
    *p=30;
    p=num+3;
    *p=40;
    p=num;
    *(p+4)=50;
    for(int i=0;i<5;i++){
        cout<<num[i]<<" ";
    }
    cout<<endl;
}

int anyMax(initializer_list<int> l)
{
    int max=0;
    for(int i :l)
    {
        if(i>max) max=i;
    }
    return max;
}

void initializer_list_test()
{
    int max=anyMax({10,2,3,4,5});
    cout<<"max="<<max<<endl;
}

void testFriend()
{
    Rectangle r(100,80);
    Rectangle r2=doubleup(r);
    cout<<"the area of r="<<r.getArea()<<endl;
    cout<<"the area of r2="<<r2.getArea()<<endl;
}

//generic class
template<class T,int N>
class arr{
   T memblk[N];
  public:
   void setmember(int x,T value);
   T getmember(int x);
};

template<class T,int N>
void arr<T,N> :: setmember(int x,T value)
{
   memblk[x]=value;
}

template<class T,int N>
T arr<T,N> :: getmember(int x)
{
   return memblk[x];
}
void testGenericClass()
{
            arr<int,5> myarr;
            arr<float,5> myfarr;
            for(int i=0;i<5;i++)
            myarr.setmember(i,100+i);
            for(int i=0;i<5;i++)
            cout<<myarr.getmember(i)<<endl;

            for(int i=0;i<5;i++)
            myfarr.setmember(i,1000+i);

            for(int i=0;i<5;i++)
            cout<<myfarr.getmember(i)<<endl;
}


void testPredefinedMarco()
{
    cout<<"line num:"<<__LINE__<<endl;
    cout<<"of file:"<<__FILE__<<endl;
    cout<<"compilation begin date:"<<__DATE__<<endl;
    cout<<"compilation begin time:"<<__TIME__<<endl;
    cout<<"and the c++ version:"<<__cplusplus<<endl;

}

//实现一个打印日志函数
#define DBGDUMP(...)\
{\
printf("%s\n%s,%d\n",__FILE__,__func__,__LINE__);\
printf(__VA_ARGS__);\
}

void testDBGDUMP()
{
   int ret=5;
  DBGDUMP("ret=%d\n",ret);
}

void charsetTest()
{
   char sz1[]="a世界a1a都去asdfad哪啦";
  string str;
  int i,len=strlen(sz1);
  for(i=0;i<len;)
  {
    if(sz1[i]<0)
    {
      str.push_back(sz1[i]);
     i++;
      str.push_back(sz1[i]);
    }
   i++;
  }
  cout<<str<<endl;
}


int main()
{
//    vector<string> strs{"i love girls","and i love pussy","i want to fuck pussy"};
//    for(string str : strs)
//    {
//        cout<<str<<" ";
//    }
//    cout<<endl;
//    cout << "Hello World!" << endl;
    //testPerson();
    //sstreamTest();
    //sstreamTest2();
    //lamfun("jack",30);
   // cout<<"5的阶乘 = "<<factorial(5)<<endl;
    //pointerTest();
   // numOps(10,20,add);
    //numOps(10,20,add);
    //numOps(10,20,sub);
    //initializer_list_test();
    //testFriend();
    //testGenericClass();
    //testPredefinedMarco();
    //testDBGDUMP();
    charsetTest();
    return 0;
}
