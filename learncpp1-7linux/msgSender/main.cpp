#include <iostream>
#include<sys/msg.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>

using namespace std;
#define MAX_TEXT 512
struct my_msg_st
{
   long int my_msg_type;
  char some_text[MAX_TEXT];
};

int main()
{
    int running=-1;
    int msgid;
    struct my_msg_st some_data;
    char buf[BUFSIZ];

    //创建消息队列
    msgid=msgget((key_t)1234,0666|IPC_CREAT);
    if(msgid==-1)//创建失败
    {
      fprintf(stderr,"msgget failed with error: %d\n",errno);
      exit(EXIT_FAILURE);
    }

    while(running)
    {
        printf("please enter some text:");
           fgets(buf,BUFSIZ,stdin);
          some_data.my_msg_type=1;
          strcpy(some_data.some_text,buf);
          if(msgsnd(msgid,(void*)&some_data,MAX_TEXT,0)==-1)
         {
             fprintf(stderr,"msgsnd failed\n");
              exit(EXIT_FAILURE);
          }
          if(strncmp(buf,"end",3)==0)
          {
            running=0;
          }

    }
     exit(EXIT_SUCCESS);
    return 0;
}
