//获取主机名
#include<stdio.h>
#include<string.h>
#include<unistd.h>

int main()
{
   char hostname[30];
   int flag=0;
   memset(hostname,0x00,sizeof(hostname));
   
   flag = gethostname(hostname,sizeof(hostname));
   if(flag<0)
   {
     perror("gethostname error");
	 return -1;
   }

   printf("hostname is :%s\n",hostname);
  return 0;
} 

