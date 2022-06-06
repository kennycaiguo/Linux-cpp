#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<arpa/inet.h> //for inet_ntoa
#include<fcntl.h>

//自定义超时时间非阻塞套接字
#define BUFFER_SIZE 1023

int setnonblocking(int fd)
{
  int old_option =fcntl(fd,F_GETFL);
  int new_option =old_option | O_NONBLOCK;
  fcntl(fd,F_SETFL,new_option);
  return old_option;
}

int unblock_connect(const char* ip,int port,int time)
{
  int ret = 0;
  struct sockaddr_in addr;
  bzero(&addr,sizeof(addr));
  inet_pton(AF_INET,ip,&addr.sin_addr);
  addr.sin_port= htons(port);

  int sockfd = socket(PF_INET,SOCK_STREAM,0);
  int fdopt = setnonblocking(sockfd);
  ret = connect(sockfd,(struct sockaddr*)(&addr),sizeof(addr));

  if(ret==0)
  {
   printf("Connect with Server immediately\n");
   fcntl(sockfd,F_SETFL,fdopt); //set the old option back;
   return sockfd;
  }
  else if(errno !=EINPROGRESS)
  {
    printf("ret =%d\n",ret);
    printf("unblock connect failed!\n");
    return -1;
  }
  else if(errno ==EINPROGRESS)
  {
    printf("unblock mode socket is connecting...\n");
  }

  fd_set readfds,writefds;
  struct timeval timeout;

  FD_ZERO(&readfds);
  FD_SET(sockfd,&writefds);

  timeout.tv_sec = time;
  timeout.tv_usec=0;

  ret = select(sockfd+1,NULL,&writefds,NULL,&timeout);
  if(ret < 0)
  {
    printf("connection time out\n");
    close(sockfd);
    return -1;
  }
  if(!FD_ISSET(sockfd,&writefds))
  {
   printf("no events on sockfd found\n");
    close(sockfd);
    return -1;
  }

  int error = 0;
  socklen_t length = sizeof(error);
  if(getsockopt(sockfd,SOL_SOCKET,SO_ERROR,&error,&length)<0)
  {
    printf("get socket option failed\n");
    close(sockfd);
    return -1;
  }
  if(error!=0)
  {
    printf("connecting failed after selected with the error:%d\n",error);
    close(sockfd);
    return -1;
  }

  //连接成功
   printf("connection ready after selected with the socket:%d\n",sockfd);
   fcntl(sockfd,F_SETFL,fdopt);
   return sockfd;
}



int main(int argc,char** argv)
{
  if(argc <= 2)
  {
    printf("usage:%s ip_address port_number\n",basename(argv[0]));
    return -1;
  }
  const char* ip=argv[1];
  int port = atoi(argv[2]);

  int sockfd = unblock_connect(ip,port,1);
  if(sockfd < 0)
  {
     printf("sockfd error!\n");
     return -1;
  }

  printf("send data out\n");
  send(sockfd,"hello",5,0);
  shutdown(sockfd,SHUT_WR);//disable read and write
  close(sockfd);

  return 0;
}
