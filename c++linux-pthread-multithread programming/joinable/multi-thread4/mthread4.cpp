#include<pthread.h>
#include<stdio.h>

typedef struct
{
  int n;
  char* str;
}DATA;

void *thfunc(void* arg)
{
   DATA* pdata;
   pdata=(DATA*)(arg);//接收传递进来的字符串
  printf("in thfunc:n=%d,str=%s\n",pdata->n,pdata->str);//输出字符串
  return (void*)0;
   
}

int main(int argc,char* argv[])
{
  pthread_t tidp;
  int ret;
  DATA pd;
  pd.n=1000;
  pd.str="hello nice people!!!";
  ret=pthread_create(&tidp,NULL,thfunc,(void*)&pd);//创建子线程并且传递str
  if(ret)
  {
     printf("pthread_create failed:%d\n",ret);
     return -1;
  }
  pthread_join(tidp,NULL);
  printf("in main:thread is created\n");
  return 0;
}

