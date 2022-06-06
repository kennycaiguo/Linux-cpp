//判断是否是阻塞套接字
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<assert.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<sys/time.h>

int main(int argc,char** argv)
{
  int sock = socket(PF_INET,SOCK_STREAM,0);
  
   assert(sock>=0);
   int old_option = fcntl(sock,F_GETFL);
   if(0==(old_option & O_NONBLOCK))
   {
     printf("this socket is in block mode\n");
   }
   else
   {
      printf("this socket is in non-block mode\n");
   }
  
  return 0;
}
