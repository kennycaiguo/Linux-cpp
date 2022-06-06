//UDP Server
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

char rbuf[50];

int main()
{
 int sockfd,size,ret;
 int on=1;
 struct sockaddr_in saddr;
 struct sockaddr_in raddr;

 //设置地址信息，ip信息
 size = sizeof(struct sockaddr_in);
 bzero(&saddr,size);
 saddr.sin_family = AF_INET;
 saddr.sin_port = htons(8888);
 saddr.sin_addr.s_addr = htonl(INADDR_ANY);

 //创建UDP套接字
 sockfd = socket(AF_INET,SOCK_DGRAM,0);
 if(sockfd < 0)
 {
   perror("socket failed");
   return -1;
 }

 //设置端口复用
 setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));

 //绑定地址，ip
 ret = bind(sockfd,(struct sockaddr*)&saddr,sizeof(struct sockaddr));
 if(ret < 0)
 {
  perror("sbind failed");
   return -1;
 }

 socklen_t val = sizeof(struct sockaddr);

 //循环接收客户端发来的信息
 while(1)
 {
   puts("waiting data");
   ret = recvfrom(sockfd,rbuf,50,0,(struct sockaddr*)&raddr,&val);
   if(ret<0)
   {
     perror("recvfrom failed");
   }

   printf("from client:%s\n",rbuf);
   bzero(rbuf,50);

 }
 //关闭套接字
 close(sockfd);

 return 0;
}

