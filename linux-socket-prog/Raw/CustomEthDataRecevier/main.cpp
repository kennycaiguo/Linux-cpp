//发送和接收自定义类型的数据帧，接收端
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/if_ether.h>
#include<netpacket/packet.h>
#include<net/if.h>
#include<net/if_arp.h>
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
#include<sys/ioctl.h>
#include<sys/shm.h>

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

void print_sockaddr_ll(struct sockaddr_ll* sa)
{
  if(sa == NULL)
  {
    return;
  }
  printf("sll_family:%d\n",sa->sll_family);
  printf("sll_protocol:%#x\n",sa->sll_protocol);
  printf("sll_ifindex:%#x\n",sa->sll_ifindex);
  printf("sll_hatype:%d\n",sa->sll_hatype);
  printf("sll_pkttype:%#x\n",sa->sll_pkttype);
  printf("sll_halen:%#x\n",sa->sll_halen);
  printf("sll_addr:%#x\n",sa->sll_addr);
}

int main()
{
  int result=0,fd,n,count=0;
  char buf[LEN];
  struct sockaddr_ll sa_recv;
  struct ifreq ifr;
  socklen_t sa_len = 0;
  char if_name[]="ens33";
  //定义以太网头结构体指针
  struct ethhdr* eth;

  //创建socket
  fd = socket(PF_PACKET,SOCK_RAW,htons(0x8902));
  if(fd<0)
  {
    perror("socket error\n");
    return errno;
  }
  //开始等待接收数据
  while(1)
  {
    memset(buf,0,sizeof(buf));
    n = recvfrom(fd,buf,sizeof(buf),0,(struct sockaddr*)&sa_recv,&sa_len);
    if(n<0)
    {
      printf("recvfrom error,%d\n",errno);
      return errno;
    }
    print_str16((unsigned char*)buf,n);//输出数据帧的内容

    eth = (struct ethhdr*)buf;
   // 从eth里提取目的mac，源mac，协议号
    printf("procotol = 0x%04x,dst mac addr:%02x:%02x:%02x:%02x:%02x:%02x\n",ntohs(eth->h_proto),
    eth->h_dest[0],eth->h_dest[1],eth->h_dest[2],eth->h_dest[3],eth->h_dest[4],eth->h_dest[5]);

    printf("procotol = 0x%04x,src mac addr:%02x:%02x:%02x:%02x:%02x:%02x\n",ntohs(eth->h_proto),
    eth->h_source[0],eth->h_source[1],eth->h_source[2],eth->h_source[3],eth->h_source[4],eth->h_source[5]);

    //输出物理层地址sa_recv的内容
    print_sockaddr_ll(&sa_recv);
    printf("sa_len:%d\n",sa_len);

  }

  return 0;
}
