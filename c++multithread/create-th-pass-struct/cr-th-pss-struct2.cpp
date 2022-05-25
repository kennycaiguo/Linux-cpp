//创建一个线程并且传入整型参数
#include<iostream>
#include<thread>

using namespace std;

typedef struct{
  const char* name;
  int age;
}person;

void thfunc(void* arg)
{
  person *p=(person*)arg;
 cout<<"thfunc:"<< p->name<<","<<p->age<<endl;
}

int main(int argc,char** argv)
{
   person p{"Jade",25};//new syntex
   //p.name="Jacklee";
   //p.age=30;

   thread t(thfunc,&p);
   t.join();
   return 0;
}

