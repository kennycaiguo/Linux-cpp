//获取本地socket地址
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<arpa/inet.h> //for inet_ntoa

int main()
{
   int sfp,nfp;
   struct sockaddr_in s_addr,c_addr;
   socklen_t sin_size;
   unsigned short portnum=10051;
   struct sockaddr_in serv;
   socklen_t  serv_len = sizeof(serv);
   
   sfp = socket(AF_INET,SOCK_STREAM,0);
   if(-1 == sfp)
   {
    printf("create socket failed!\r\n");
	return -1;
   }
   printf("create socket with success!\r\n");
   printf("ip = %s,port = %d\r\n",inet_ntoa(serv.sin_addr),ntohs(serv.sin_port));
   
   int on=1;
   setsockopt(sfp,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));//设置也许地址的立即重用
   bzero(&s_addr,sizeof( struct sockaddr_in));
   s_addr.sin_family = AF_INET;
   s_addr.sin_addr.s_addr = inet_addr("172.26.207.83 ");//必须是本机的地址
   s_addr.sin_port = htons(portnum);
   
   if(-1 == bind(sfp,(struct sockaddr*)(&s_addr),sizeof(struct sockaddr)))//绑定
   {
     printf("bind socket failed!!\r\n");
	 return -1;
   }
   printf("bind with success\r\n");
   getsockname(sfp,(struct sockaddr*)(&serv),&serv_len);//获取本地socket地址
   printf("ip = %s,port = %d\r\n",inet_ntoa(serv.sin_addr),ntohs(serv.sin_port));
   return 0;
}


