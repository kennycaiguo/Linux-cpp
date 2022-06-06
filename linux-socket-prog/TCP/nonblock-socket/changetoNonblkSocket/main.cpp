#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<arpa/inet.h> //for inet_ntoa
#include<fcntl.h>


int setnonblocking(int fd)
{
 int old_option = fcntl(fd,F_GETFL);
 int new_option = old_option | O_NONBLOCK;
 fcntl(fd,F_SETFL,new_option);
 return old_option;
}

int main(int argc,char** argv)
{
  int sock = socket(PF_INET,SOCK_STREAM,0);
  assert(sock >=0);

   int old_option=fcntl(sock,F_GETFL);
   if(0==(old_option & O_NONBLOCK))
      printf("socket is in block mode\n"); //0 is block mode
   else
       printf("socket is in nonblock mode\n"); //0 is block mode

   setnonblocking(sock);
   old_option=fcntl(sock,F_GETFL);
   if(0==(old_option & O_NONBLOCK))
      printf("socket is in block mode\n"); //0 is block mode
   else
       printf("socket is in nonblock mode\n"); //0 is block mode
   return 0;
}
