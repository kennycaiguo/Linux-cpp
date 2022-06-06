//chat client
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<arpa/inet.h>
#include<time.h>
#include<fcntl.h>
#include<sys/ioctl.h>

#define BUFFER_SIZE 1023

int setnonblocking(int fd)
{
  int old_opt = fcntl(fd,F_GETFL);
  int new_opt = old_opt | O_NONBLOCK;
  fcntl(fd,F_SETFL,new_opt);
  return old_opt;
}

int unblock_connect(const char* ip,int port,int time)
{
  int ret = 0;
  struct sockaddr_in addr;
  bzero(&addr,sizeof(addr));
  addr.sin_family = AF_INET;
  inet_pton(AF_INET,ip,&addr.sin_addr);
  addr.sin_port = htons(port);

  int sockfd = socket(PF_INET,SOCK_STREAM,0);
  int fdopt = setnonblocking(sockfd);
  ret= connect(sockfd,(struct sockaddr*)&addr,sizeof(addr));

  printf("connect ret code = %d\n",ret);
  if(ret == 0)
  {
    printf("connect with server immadiately\n");
    fcntl(sockfd,F_SETFL,fdopt); //set the old option back
    return sockfd;
  }
  else if(errno !=EINPROGRESS)
  {
    printf("ret=%d\n",ret);
    printf("unblock connect failed\n");
    return -1;
  }
  else if(errno ==EINPROGRESS)
  {
    printf("unblock socket is connecting...\n");
  }

  fd_set readfds,writefds;
  struct timeval timeout;
  FD_ZERO(&readfds);
  FD_SET(sockfd,&writefds);

  timeout.tv_sec = time; //timeout is 10minutes
  timeout.tv_usec = 0;

  ret = select(sockfd+1,NULL,&writefds,NULL,&timeout);
  if(ret <=0)
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
  if(getsockopt(sockfd,SOL_SOCKET,SO_ERROR,&error,&length) < 0)
  {
    printf("get socket option failed \n");
    close(sockfd);
    return -1;
  }
  if(error !=1)
  {
    printf("connection failed after select with the error:%d \n",error);
    close(sockfd);
    return -1;
  }
  //connection successful
  printf("connection ready after select with socket:%d\n",sockfd);
  fcntl(sockfd,F_SETFL,fdopt); //set old option back
  printf("connect ok\r\n");

  int recbytes;
  int sin_size;
  char buffer[1024]={0};

  if(-1==(recbytes = read(sockfd,buffer,1024)))//接收数据
  {
    printf("read data failed \n");
    return -1;
  }
  printf("read ok\n");

  buffer[recbytes]='\0';
  printf("%s\r\n",buffer);

  return sockfd;
}

int main()
{
  unsigned short port = 10051;
  char ip[]="172.26.207.83";
  int sockfd = unblock_connect(ip,port,1);
  if(sockfd < 0)
  {
   printf("sockfd error!\n");
   return -1;
  }

  close(sockfd);//关闭套接字
  return 0;
}
