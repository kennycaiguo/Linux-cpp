//UDP版本的获取ip
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<net/if.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<arpa/inet.h>
#include<sys/ioctl.h>

int main()
{
   int inet_sock;
   struct ifreq ifr; //定义网口请求结构体
   inet_sock = socket(AF_INET,SOCK_DGRAM,0); //创建UDP套接字

   strcpy(ifr.ifr_name,"ens33");
   if(ioctl(inet_sock,SIOCGIFADDR,&ifr)<0)
      perror("ioctl");

   printf("%s\n",inet_ntoa(((struct sockaddr_in*)&(ifr.ifr_addr))->sin_addr));



  return 0;
}



