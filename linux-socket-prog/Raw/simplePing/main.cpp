//实现简单ping功能
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/time.h>
#include<sys/socket.h>
#include<netpacket/packet.h>
#include<net/if.h>
#include<net/if_arp.h>
#include<netinet/in.h>
#include<netinet/ip_icmp.h>
#include<unistd.h>
#include<netdb.h>
#include<string.h>
#include<errno.h>
#include<arpa/inet.h>
#include<sys/ioctl.h>
#include<signal.h>

#define MAX_SIZE 1024

char send_buf[MAX_SIZE];
char recv_buf[MAX_SIZE];

int nsend=0, nrecv=0;
int datalen = 56;

//统计
void statistics(int signum)
{
  printf("\n-----------------------PING statistics-----------------------\n");
  printf("%d packets transmitted,%d received,%%%d lost\n",nsend,nrecv,(nsend-nrecv)/nsend*100);
  exit(EXIT_SUCCESS);
}

//校验和算法
int calc_chsum(unsigned short* addr,int len)
{
  int sum=0,n=len;
  unsigned short answer=0;
  unsigned short* p = addr;

  //每两个字节相加
  while(n>1)
  {
    sum += *p++;
    n -=2;
  }
  //处理数据大小是奇数，在最后一个字节后面补0
  if(n==1)
  {
    *((unsigned char*)&answer)=*(unsigned char*)p;
    sum +=answer;
  }
  //将得到的sum值的高2字节和低2字节相加
  sum = (sum>>16) + (sum & 0xffff);

  //处理溢出的情况
  sum +=sum >> 16;
  answer = ~sum;
  return answer;
}

int pack(int pack_num)
{
  int packsize;
  struct icmp* icmp;
  struct timeval* tv;

  icmp = (struct icmp*)send_buf;
  icmp->icmp_type = ICMP_ECHO;
  icmp->icmp_code = 0;
  icmp->icmp_cksum = 0;
  icmp->icmp_id = htons(getpid());
  icmp->icmp_seq = htons(pack_num);

  tv = (struct timeval*)icmp->icmp_data;

  //记录发送时间
  if(gettimeofday(tv,NULL) < 0)
  {
     perror("Failed to get time of the day");
     return -1;
  }

  packsize = 8 + datalen;
  icmp-> icmp_cksum = calc_chsum((unsigned short*)icmp,packsize);
  return packsize;
}

int send_packet(int sockfd,struct sockaddr* paddr)
{
  int packsize;
  //将send_buf填上a
  memset(send_buf,'a',sizeof(send_buf));
  nsend++;
  packsize = pack(nsend);
  //send
  if(sendto(sockfd,send_buf,packsize,0,paddr,sizeof(struct sockaddr))<0)
  {
     perror("Fail to sendto");
     return -1;
  }

  return 0;
}


struct timeval time_stab(struct timeval* tv_send,struct timeval* tv_recv)
{
  struct timeval ts;
  if(tv_recv->tv_usec - tv_send->tv_usec <0)
  {
    tv_recv->tv_sec--;
    tv_recv->tv_usec +=1000000;
  }

  ts.tv_sec =  tv_recv->tv_sec - tv_send->tv_sec;
  ts.tv_usec = tv_recv->tv_usec - tv_send->tv_usec;
  return ts;

}

int unpack(int len,struct timeval* tv_recv,sockaddr* paddr,char* ipname)
{
  struct ip* ip;
  struct icmp* icmp;
  struct timeval* tv_send,ts;

  int ip_head_len;
  float rtt;

  ip = ( struct ip*)recv_buf;
  ip_head_len = ip->ip_hl << 2;
  icmp =(struct icmp*)(recv_buf + ip_head_len);

  len -=ip_head_len;
  if(len < 8)
  {
    printf("ICMP packets\'s is less than 8.\n");
    return -1;
  }

  if(ntohs(icmp->icmp_id)== getpid() && icmp->icmp_type == ICMP_ECHOREPLY)
  {
    nrecv++;
    tv_send = (struct timeval*)icmp->icmp_data;
    ts = time_stab(tv_send,tv_recv);

    rtt = ts.tv_sec * 1000 + (float)ts.tv_usec/1000;//以毫秒为单位
    printf("%d bytes from %s (%s):icmp_req = %d ttl = %d time=%.3fml.\n",len
    ,ipname,
    inet_ntoa(((struct sockaddr_in*)paddr)->sin_addr),
    ntohs(icmp->icmp_seq),
    ip->ip_ttl,rtt);
  }

  return 0;
}


int recv_packet(int sockfd,char* ipname)
{
  socklen_t addr_len,n;
  struct timeval ts;
  struct sockaddr from_addr;

  addr_len = sizeof(struct sockaddr);
  if((n = recvfrom(sockfd,recv_buf,sizeof(recv_buf),0,&from_addr,&addr_len))<0)
  {
     perror("Fail to recvfrom");
     return -1;
  }

  if(gettimeofday(&ts,NULL) < 0)
  {
    perror("Fail to get time of day");
    return -1;
  }

  unpack(n,&ts,&from_addr,ipname);

  return 0;

}


int main(int argc,char** argv)
{
  int size =50 * 1024;
  int sockfd,netaddr;
  struct protoent* protocol;
  struct hostent* host;
  struct sockaddr_in peer_addr;

  if(argc <2)
  {
    fprintf(stderr,"usage: %s ip\n",argv[0]);
    exit(EXIT_FAILURE);
  }

  //获取icmp信息
  if((protocol = getprotobyname("icmp"))==NULL)
  {
    perror("Fail to getprotobyname");
    exit(EXIT_FAILURE);
  }
  //创建原始套接字
  if((sockfd = socket(AF_INET,SOCK_RAW,protocol->p_proto))<0)
  {
    perror("Fail to init socket");
    exit(EXIT_FAILURE);
  }

  //回收root权限,设置当前用户权限
  setuid(getuid());

  //扩大套接字缓冲区到50kb，这样做主要是为了减少接收缓冲区溢出的可能性
  if(setsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,&size,sizeof(size)) <0)
  {
     perror("Fail to init socket");
     exit(EXIT_FAILURE);
  }

  //填充对方地址
  bzero(&peer_addr,sizeof(peer_addr));
  peer_addr.sin_family = AF_INET;

  //判断是主机(域名)还是IP
  if((netaddr = inet_addr(argv[1]))== INADDR_NONE)
  {
    //是主机(域名)
    if((host = gethostbyname(argv[1]))== NULL)
    {
      fprintf(stderr," %s unknown host : %s\n",argv[0],argv[1]);
      exit(EXIT_FAILURE);
    }
    memcpy((char*)&peer_addr.sin_addr,host->h_addr,host->h_length);
  }
  else //是IP地址
  {
    peer_addr.sin_addr.s_addr = netaddr;
  }

  //注册信号处理函数
  signal(SIGALRM,statistics);
  signal(SIGINT,statistics);
  alarm(5);

  //输出开始信息
  printf("PING %s(%s) %d bytes of data .\n",argv[1],inet_ntoa(peer_addr.sin_addr),datalen);

  //发送和接收报文
  while(1)
  {
    send_packet(sockfd,(struct sockaddr*)&peer_addr);
    recv_packet(sockfd,argv[1]);
    alarm(5);
    sleep(1);
  }

  exit(EXIT_SUCCESS);
}
