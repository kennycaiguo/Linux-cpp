//发送端
//自定义链路层数据发送端
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netpacket/packet.h>
#include<net/if.h>
#include<net/if_arp.h>
#include<string.h>
#include<errno.h>
#include<arpa/inet.h>
#include<sys/ioctl.h>

#define LEN 60

void print_str16(unsigned char buf[],size_t len)
{
  int i;
  unsigned char c;
  if(buf==NULL || len<=0)
  {
    return;
  }

  for(i=0;i<len;i++)
  {
    c = buf[i];
    printf("%02x",c);
  }
  printf("\n");

}

int main()
{
   int result=0,fd,n,count=3,nsend=0; //count=3表示要发送3个数据包
   char buf[LEN];

  struct sockaddr_ll sa;
  struct ifreq ifr;
  char if_name[]="ens33";
  // mac:00:0c:29:cd:40:35
  char dst_mac[6]={0x00,0x0c,0x29,(char)0xcd,0x40,0x35};
  char src_mac[6];
  short type = htons(0x8902);
  memset(&sa,0,sizeof(struct sockaddr_ll));
   memset(buf,0,sizeof(buf));

  //创建socket
  fd = socket(PF_PACKET,SOCK_RAW,htons(0x8902));
  if(fd<0)
  {
    perror("socket error\n");
    return errno;
  }

  //获得网卡索引号
  strcpy(ifr.ifr_name,if_name);
  result = ioctl(fd,SIOCGIFINDEX,&ifr);
  if(result!=0)
  {
    printf("get mac index error,%d\n",errno);
    return errno;
  }

  sa.sll_ifindex = ifr.ifr_ifindex;//赋值给物理层地址
  //得到源mac地址，即本机要发送数据的网卡的mac地址
  result = ioctl(fd,SIOCGIFHWADDR,&ifr);
  if(result!=0)
  {
    printf("get mac address error,%d\n",errno);
    return errno;
  }
  memcpy(src_mac,ifr.ifr_hwaddr.sa_data,6);

  //设置数据给以太网数据帧头
  memcpy(buf,dst_mac,6);
  memcpy(buf+6,src_mac,6);
  memcpy(buf+12,&type,2);

  print_str16((unsigned char*)buf,sizeof(buf));//输出我们要发送的数据帧
  //准备发送数据
  while(count-- >0)
  {
    n = sendto(fd,buf,sizeof(buf),0,(struct sockaddr*)&sa,sizeof(struct sockaddr_ll));
    if(n<0)
    {
       printf("sendto error,%d\n",errno);
       return errno;
    }
    printf("sendto msg %d,len %d\n",++nsend,n);
  }
  return 0;
}
