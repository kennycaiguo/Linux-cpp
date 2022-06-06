//获取网卡ip地址，原始套接字版本

#include<stdio.h>
#include<sys/socket.h>
#include<net/if.h>
#include<string.h>
#include<errno.h>
#include<arpa/inet.h>
#include<sys/ioctl.h>
#include<netinet/in.h>

int main()
{
   int inet_sock;
   struct ifreq ifr; //定义网卡请求结构体
   inet_sock = socket(AF_INET,SOCK_RAW,IPPROTO_TCP);
   strcpy(ifr.ifr_name,"ens37");
   //SIOCGIFADDR标志代表获取接口地址
   if(ioctl(inet_sock,SIOCGIFADDR,&ifr)<0)
   {
     perror("ioctl");
   }
   printf("%s\n",inet_ntoa(((struct sockaddr_in*)&(ifr.ifr_addr))->sin_addr));

  return 0;
}
