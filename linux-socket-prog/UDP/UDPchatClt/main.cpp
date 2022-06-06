//UDPClient
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<arpa/inet.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<dirent.h>
#include<sys/mman.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/msg.h>
#include<sys/sem.h>
#include<pthread.h>
#include<semaphore.h>
#include<poll.h>
#include<sys/epoll.h>

char wbuf[50];

int main()
{
  int sockfd,size,ret;
  int on=1;
  struct sockaddr_in saddr;

  size = sizeof(struct sockaddr_in);
  bzero(&saddr,size);
  //设置地址信息，ip信息
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(8888);
  saddr.sin_addr.s_addr = inet_addr("172.26.207.83");//服务器IP地址

 //创建UDP套接字
 sockfd = socket(AF_INET,SOCK_DGRAM,0);
 if(sockfd < 0)
 {
   perror("socket failed");
   return -1;
 }

 //设置端口复用
 setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
 //循环发送信息给服务器
 while(1)
 {
   puts("please enter data:");
   scanf("%s",wbuf);//here there is a problem.scanf can only enter a word at a time,if you try to enter a sentence,it will be split to multi words.
   ret = sendto(sockfd,wbuf,50,0,(struct sockaddr*)&saddr,sizeof(struct sockaddr));
   if(ret < 0)
   {
      perror("sendto server failed");
   }

   bzero(wbuf,50);

 }

  close(sockfd);


  return 0;
}
