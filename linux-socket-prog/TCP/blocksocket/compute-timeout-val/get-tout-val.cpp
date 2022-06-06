//统计阻塞套接字的超时时间
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<assert.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<sys/time.h>

#define  BUFFER_SIZE 512

int main(int argc,char** argv)
{
   char ip[]="172.26.207.85"; //输入一个不存在的ip用来测试超时时间
   int port = 13334;
   
   struct sockaddr_in srv_addr;
   bzero(&srv_addr,sizeof(srv_addr));
   srv_addr.sin_family= AF_INET;
   inet_pton(AF_INET,ip,&srv_addr.sin_addr);
   srv_addr.sin_port=htons(port);
   
   int sock = socket(PF_INET,SOCK_STREAM,0);
   assert(sock >= 0);
   
   int old_option = fcntl(sock,F_GETFL);
   printf("noblock: %d\n",old_option & O_NONBLOCK);//阻塞模式
   
   struct timeval tv1,tv2;
   gettimeofday(&tv1,NULL);
   
   int ret = connect(sock,(struct sockaddr*)(&srv_addr),sizeof(srv_addr));
   
   printf("connect return code:%d\n",ret);
   if(ret==0)
   {
     printf("call getsockname...\n");
	 struct sockaddr_in loc_addr;
	 socklen_t length;
	 
	 ret = getpeername(sock,(struct sockaddr*)(&loc_addr),&length);
	 assert(ret==0);
	 
	 char local[INET_ADDRSTRLEN];
	 printf("local with ip:%s and port:%d\n",
	 inet_ntop(AF_INET,&loc_addr.sin_addr,local,INET_ADDRSTRLEN),
	 ntohs(loc_addr.sin_port));
	 
	 char buf[BUFFER_SIZE];
	 memset(buf,'a',BUFFER_SIZE);
	 send(sock,buf,BUFFER_SIZE,0);
	 
   }
   else if(ret==-1)
   {
     gettimeofday(&tv2,NULL);
	 suseconds_t msec = tv2.tv_usec-tv1.tv_usec;
	 time_t sec = tv2.tv_sec-tv1.tv_sec;
	 printf("time used:%d.%fs\n",sec,(double)msec/1000000);
	 printf("connect failed...\n");
	 if(errno==EINPROGRESS)
	 {
	   printf("unblcok mode ret code ....\n");
	 }
   }
   else{
       printf(" ret code is:%d\n",ret);
   }
   
   close(sock);
   return 0;
}
