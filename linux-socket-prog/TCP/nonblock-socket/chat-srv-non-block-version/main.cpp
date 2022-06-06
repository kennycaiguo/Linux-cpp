#//服务器客户机聊天程序非阻塞-服务器
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<arpa/inet.h>

int main()
{
  int sfp,nfp;
  struct sockaddr_in s_addr,c_addr;
  socklen_t sin_size;
  unsigned short portnum=10051;

  printf("Hello,i am a server,Welcome to connect me!\r\n");
  sfp = socket(AF_INET,SOCK_STREAM,0);
  if(-1==sfp)
  {
    printf("socket failed!\r\n");
    return -1;
  }
  printf("socket ok!\r\n");

  int on=1;
  setsockopt(sfp,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));//允许地址立即重用

  bzero(&s_addr,sizeof(struct sockaddr_in));
  s_addr.sin_family=AF_INET;
  s_addr.sin_addr.s_addr=htonl(INADDR_ANY);
  s_addr.sin_port=htons(portnum);

  if(-1==bind(sfp,(struct sockaddr*)(&s_addr),sizeof(struct sockaddr)))
  {
    printf("bind failed:%d!\r\n",errno);
    return -1;

  }
  printf("bind ok\r\n");

  if(-1==listen(sfp,5))
  {
    printf("listen failed!\r\n");
    return -1;
  }
  printf("listen ok\r\n");

  while(1)
  {
    sin_size = sizeof(struct sockaddr_in);
    nfp = accept(sfp,(struct sockaddr*)(&c_addr),&sin_size);
    if(-1==nfp)
    {
       printf("accept failed!\r\n");
       return -1;
    }
    printf("accept ok\r\nServer start get connect from ip=%s,port=%d\r\n",inet_ntoa(c_addr.sin_addr),ntohs(c_addr.sin_port));
    if(-1==write(nfp,"hello client,nice to meet you!!\r\n",32))
    {
       printf("write failed!\r\n");
       return -1;
    }
    printf("write ok\r\n");
    close(nfp);
    puts("continue to listen(y/n)?");
    char ch[2];
    scanf("%s",ch,2);
    if(ch[0] !='y')
       break;
  }
  printf("bye!\n");
  close(sfp);//关闭套接字
  return 0;
}
