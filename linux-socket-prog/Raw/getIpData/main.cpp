//直接抓取IP报文，输出IP地址
#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<arpa/inet.h>
#include<netinet/ether.h>
#include<netinet/if_ether.h>

int main(int argc,char** argv)
{
  int sock,n;
   char buffer[2048];

  //定义以太网头结构体指针
  struct ethhdr* eth;
  struct iphdr* iph;
  struct in_addr addr1,addr2;
  long cn = 1;
  if(0 >(sock= socket(PF_PACKET,SOCK_RAW,htons(ETH_P_IP))))
  {
    perror("socket");
    exit(1);
  }

  while(1)
  {
    //获取数据链路层的数据帧
    n = recvfrom(sock,buffer,sizeof(buffer),0,NULL,NULL);
    printf("==========================count = %d==========================",cn++);
    printf("%d bytes read\n",n);
    //接收到的数据帧前6字节是目的MAC地址，紧接的6给字节是源MAC地址
    eth = (struct ethhdr*)buffer;

    //从eth里提取目的mac，源mac，协议号
    printf("Dest MAC addr:%02x:%02x:%02x:%02x:%02x:%02x:\n",
      eth->h_dest[0], eth->h_dest[1], eth->h_dest[2], eth->h_dest[3], eth->h_dest[4], eth->h_dest[5]);
    printf("Sour MAC addr:%02x:%02x:%02x:%02x:%02x:%02x:\n",
      eth->h_source[0], eth->h_source[1], eth->h_source[2], eth->h_source[3], eth->h_source[4], eth->h_source[5]);
    iph = (struct iphdr*)(buffer + sizeof(struct ethhdr));

    memcpy(&addr1,&iph->saddr,4);//复制源IP地址
    memcpy(&addr2,&iph->daddr,4);//复制目的IP地址

    //我们只对IPv4且没有选项字段的IPv4报文感兴趣
    if(iph->version == 4 && iph->ihl == 5)
    {
      printf("Source host:%s\n",inet_ntoa(addr1));
      printf("Dest host:%s\n",inet_ntoa(addr2));
    }
  }
  return 0;
}
