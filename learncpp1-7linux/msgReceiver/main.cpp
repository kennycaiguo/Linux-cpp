#include<sys/msg.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>

struct my_msg_st
{
   long int my_msg_type;
  char some_text[BUFSIZ];
};

int main()
{
   int running=-1;
   int msgid;
   struct my_msg_st some_data;
   long int msg_to_receive=0;//读取消息队列中的全部消息

  //创建消息队列
  msgid=msgget((key_t)1234,0666|IPC_CREAT);
  if(msgid==-1)//创建失败
  {
    fprintf(stderr,"msgget failed with error: %d\n",errno);
    exit(EXIT_FAILURE);
  }
  //接收消息队列的信息一直遇到end消息。最后，消息队列被删除
  while(running)
  {
     //阻塞方式等待接收消息
    if(msgrcv(msgid,(void*)&some_data,BUFSIZ,msg_to_receive,0)==-1)
   {
     fprintf(stderr,"msgrcv failed with errno: %d\n",errno);
     exit(EXIT_FAILURE);
   }
   printf("You Wrote: %s",some_data.some_text);
  if(strncmp(some_data.some_text,"end",3)==0)//如果收到end消息就退出循环
   {
     running=0;
    }
  }
  if(msgctl(msgid,IPC_RMID,0)==-1)//删除消息队列
  {
     fprintf(stderr,"msgctl(IPC_RMID) failed \n");
     exit(EXIT_FAILURE);
  }
  return 0;
}
