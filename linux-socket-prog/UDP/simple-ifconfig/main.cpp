//简单实现ifconfig功能
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/ioctl.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<arpa/inet.h>
#include<linux/sockios.h>
#include<net/if.h>
#define MAX_INTERFACE (16)

void port_status(unsigned int flags);

int set_if_flags(char* pif_name,int sock,int status,int set)
{
 struct ifreq ifr;
 int ret=0;

 strncpy(ifr.ifr_name,pif_name,strlen(pif_name)+1);
 ret = ioctl(sock,SIOCGIFFLAGS,*&ifr);

 if(ret)
    return -1;

 //set or clean
 if(set)
    ifr.ifr_flags |=status;
 else
    ifr.ifr_flags &=~status;

 //set the flags
 ret = ioctl(sock,SIOCGIFFLAGS,&ifr);
 if(ret) return -1;
 return 0;

}

int get_if_info(int fd)
{
  struct ifreq buf[MAX_INTERFACE];
  struct ifconf ifc;

  int ret=0,if_num=0;
  ifc.ifc_len = sizeof(buf);
  ifc.ifc_buf = (caddr_t)buf;

  ret = ioctl(fd,SIOCGIFCONF,(char*)&ifc);
  if(ret)
  {
    printf("get if config info failed");
    return -1;
  }

  //网口总数ifc.ifc_len应该是一个输出参数
  if_num = ifc.ifc_len/sizeof(struct ifreq);
  printf("interface num is interface = %d\n",if_num);
  while(if_num-- >0)
  {
    printf("net device:%s\n",buf[if_num].ifr_name);
    //获取第n个网口信息
    ret = ioctl(fd,SIOCGIFFLAGS,(char*)&buf[if_num]);
    if(ret) continue;
    //获取网口状态
    port_status(buf[if_num].ifr_flags);
    //获取当前网卡的ip地址
    ret = ioctl(fd,SIOCGIFADDR,(char*)&buf[if_num]);
    if(ret) continue;
    printf("IP address is:\n%s\n",inet_ntoa(((struct sockaddr_in*)(&buf[if_num].ifr_addr))->sin_addr));

    //获取当前网卡的mac地址
    ret = ioctl(fd,SIOCGIFHWADDR,(char*)&buf[if_num]);
    if(ret) continue;
    printf("%02x:%02x:%02x:%02x:%02x:%02x\n\n",
           (unsigned char)buf[if_num].ifr_hwaddr.sa_data[0],
           (unsigned char)buf[if_num].ifr_hwaddr.sa_data[1],
           (unsigned char)buf[if_num].ifr_hwaddr.sa_data[2],
           (unsigned char)buf[if_num].ifr_hwaddr.sa_data[3],
           (unsigned char)buf[if_num].ifr_hwaddr.sa_data[4],
           (unsigned char)buf[if_num].ifr_hwaddr.sa_data[5]);
  }
}

void port_status(unsigned int flags)
{
  if(flags & IFF_UP)
  {
    printf("is up\n");
  }
  //2
  if(flags & IFF_BROADCAST)
  {
    printf("is broadcast\n");
  }
  //3
  if(flags & IFF_LOOPBACK)
  {
    printf("is loop back\n");
  }
  //4
  if(flags & IFF_POINTOPOINT)
  {
    printf("is point to point\n");
  }
  //5
  if(flags & IFF_RUNNING)
  {
    printf("is running\n");
  }
  //6
   if(flags & IFF_PROMISC)
  {
    printf("is promisc\n");
  }
}

int main()
{
  int fd;
  fd = socket(AF_INET,SOCK_DGRAM,0);
  if(fd>0)
  {
    get_if_info(fd);
    close(fd);
  }

  return 0;
}


