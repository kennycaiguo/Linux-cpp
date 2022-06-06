#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<netdb.h>
#include<sys/types.h>
#include<netinet/in.h>

int main(int argc ,char** argv)
{
  struct hostent* h;
  if(argc !=2)
  {
     fprintf(stderr,"usage: getip address\n");
	 return -1;
  }
  
  if((h = gethostbyname(argv[1]))==NULL)
  {
    herror("gethostbyname");
	return -1;
  }
  printf("host name:%s\n",h->h_name);
  printf("Ip Address: %s\n",inet_ntoa(*((struct hostent*)h->h_addr)));
   
   return 0;
}
