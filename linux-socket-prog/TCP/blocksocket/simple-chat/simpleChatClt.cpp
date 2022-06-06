#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<arpa/inet.h>

int main()
{
  int cfd;
  int recbytes;
  int sin_size;
  char buffer[1024]={0};
  struct sockaddr_in s_addr,c_addr;
  unsigned short portnum=10051;
  char ip[]="172.26.207.83";
  
  printf("this is client\r\n");
  
  cfd=socket(AF_INET,SOCK_STREAM,0);
  if(-1==cfd)
  {
    printf("create socket failed\r\n");
	return -1;
  }
   printf("socket ok!\r\n");
   bzero(&s_addr,sizeof(s_addr));
   s_addr.sin_family=AF_INET;
   s_addr.sin_addr.s_addr=inet_addr(ip);
   s_addr.sin_port=htons(portnum);
   
   if(-1==connect(cfd,(struct sockaddr*)(&s_addr),sizeof(struct sockaddr)))//发起连接
   {
    printf("connect failed\r\n");
	return -1;
   }
   printf("connect ok!\r\n");
   if(-1==(recbytes = read(cfd,buffer,1024)))
   {
    printf("read data failed\r\n");
	return -1;
   }
   printf("read ok!\r\n");
   buffer[recbytes]='\0';
   printf("message:%s\r\n",buffer);
   
   printf("Press any key to quit");
   getchar();
   close(cfd);//关闭套接字
  return 0;
}
