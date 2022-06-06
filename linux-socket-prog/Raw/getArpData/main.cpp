//获取arp数据
#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<arpa/inet.h>
#include<netinet/ether.h>

int main(int argc,char** argv)
{
  int i=0;
  unsigned char buf[1024]=" ";

  //定义以太网头结构体指针
  struct ethhdr* eth;
  int sock_raw_fd = socket(PF_PACKET,SOCK_RAW,htons(ETH_P_ARP));
  while(1)
  {
    //获取数据链路层的数据帧
    recvfrom(sock_raw_fd,buf,sizeof(buf),0,NULL,NULL);
    eth = (struct ethhdr*)buf;
    //从eth里提取目的mac，源mac，协议号
    printf("protocol:0x%04x,dst mac:%02x:%02x:%02x:%02x:%02x:%02x:\n",ntohs(eth->h_proto),
      eth->h_dest[0], eth->h_dest[1], eth->h_dest[2], eth->h_dest[3], eth->h_dest[4], eth->h_dest[5]);
    printf("protocol:0x%04x,src mac:%02x:%02x:%02x:%02x:%02x:%02x:\n",ntohs(eth->h_proto),
      eth->h_source[0], eth->h_source[1], eth->h_source[2], eth->h_source[3], eth->h_source[4], eth->h_source[5]);

  }
  return 0;
}
