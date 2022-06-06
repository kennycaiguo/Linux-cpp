//get Mac
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/ioctl.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<bits/ioctls.h>
#include<arpa/inet.h>
#include<linux/sockios.h>
#include<linux/if_packet.h>
#include<net/ethernet.h>
#include<net/if.h>
#include<linux/if_ether.h>

#define IFRNAME "ens33"
unsigned char dst_mac[6]={0};

int main()
{
  int i,datalen,sd;
  struct sockaddr_ll device;
  struct ifreq ifr; //定义网口的信息请求结构体

  bzero(&ifr,sizeof(struct ifreq));
  //创建原始套接字
  if((sd = socket(PF_PACKET,SOCK_DGRAM,htons(ETH_P_ALL)))<0)
  {
    printf("socket() failed to get socket descriptor for using ioctl()");
    return (EXIT_FAILURE);
  }

  memcpy(ifr.ifr_name,IFRNAME,sizeof(struct ifreq));
  if(ioctl(sd,SIOCGIFHWADDR,&ifr)<0)
  {
     printf("ioctl() failed to get source Mac address");
    return (EXIT_FAILURE);
  }

  close(sd);
  memcpy(dst_mac,ifr.ifr_hwaddr.sa_data,6);

  //输出结果
  printf("mac address:%02x:%02x:%02x:%02x:%02x:%02x:\n",dst_mac[0],
      dst_mac[1],dst_mac[2],dst_mac[3],dst_mac[4],dst_mac[5]);


  return 0;
}
