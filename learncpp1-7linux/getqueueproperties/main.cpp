#include <iostream>
#include<sys/types.h>
#include<sys/msg.h>
#include<unistd.h>
#include<ctime>
#include<stdio.h>
#include<errno.h>

using namespace std;

void msg_stat(int,struct msqid_ds);


int main()
{

    int gflags,sflags,rflags;
      key_t key;
      int msgid;
     int reval;
     struct msgsbuf{
         int mtype;
         char mtext[1];
    }msg_sbuf;

    struct msgmbuf{
         int mtype;
         char mtext[10];
    }msg_rbuf;

    struct msqid_ds msg_ginfo,msg_sinfo;
    char msgpath[]="./test.txt";
    key=ftok(msgpath,'b');
     gflags=IPC_CREAT|IPC_EXCL;
    msgid=msgget(key,gflags|00666);
    if(msgid==-1)
    {
       printf("msg create failed\n");

     }
     //创建一个消息队列后，输出消息队列的默认属性
    msg_stat(msgid,msg_ginfo);
    sflags=IPC_NOWAIT;
    msg_sbuf.mtype=10;
    msg_sbuf.mtext[0]='a';
    reval=msgsnd(msgid,&msg_sbuf,sizeof(msg_sbuf.mtext),sflags);
    if(reval==-1)
    {
      printf("message send failed\n");
    }
    //发送一个消息后，输出消息队列的属性
     msg_stat(msgid,msg_ginfo);
    reval=msgctl(msgid,IPC_RMID,NULL);//删除消息队列
    if(reval==-1)
    {
      printf("unlink msg queue error\n");
     }
     return 0;
}

void msg_stat(int msgid,struct msqid_ds msg_info)
{
    int reval ;
    sleep(1);//只是为了后面删除时间方便
    reval=msgctl(msgid,IPC_CREAT,&msg_info);
    if(reval==-1)
    {
     printf("get msg info error\n");
    }
    printf("\n");
    printf("current number of bytes on queue is %d\n",msg_info.msg_cbytes);
    printf(" number of messages in queue is %d\n",msg_info.msg_qnum);
    printf("max number of bytes on queue is %d\n",msg_info.msg_qbytes);
    //每个消息队列的容量（字节数）都有限制MSGMNB,值的大小因系统而异。
    //在创建新的消息队列时，msg_qbytes的默认值就是MSGMNB
    printf("pid of last msgsnd is %d\n",msg_info.msg_lspid);
    printf("pid of last msgrcv is %d\n",msg_info.msg_lrpid);
    printf("last msgsnd time is %s\n",ctime(&(msg_info.msg_stime)));
    printf("last msgrcv time  is  %s\n",ctime(&(msg_info.msg_rtime)));
    printf("last change time  is  %s\n",ctime(&(msg_info.msg_ctime)));
    printf("msg uid is %d\n",msg_info.msg_perm.uid);
    printf("msg gid is %d\n",msg_info.msg_perm.gid);

}
