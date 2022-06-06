#include<iostream>
using namespace std;

int main(int argc,char** argv)
{
    int num=0x12345678;
     char* p=(char*)&num;
      if(*p==0x12)
             cout<<"this machine is big endian\n";
      else
             cout<<"this machine is little endian\n";

   return 0;
}
