//openssl sample
#include<iostream>
using namespace std;
#include "openssl/evp.h"

int main()
{
  char sz[]="Hello OpenSSL";
  cout<<sz<<endl;
  OpenSSL_add_all_algorithms();//加载所有SSL算法
   
  return 0;
}
