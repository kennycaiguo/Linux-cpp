#include <iostream>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<signal.h>

using namespace std;

#define MAXFILE 65535

volatile sig_atomic_t _running=1;

void sigterm_handler(int arg)
{
  _running = 0;
}

int main()
{
    pid_t pc;
    int i,fd,len;
    char* buf="this is a Daemon\n";
    len=strlen(buf);
    pc=fork();//1.fork
    if(pc<0)
    {
       printf("error forking process\n");
      exit(1);
    }
    else if(pc>0) exit(0);//使得父进程退出
    setsid();//2.setsid
    chdir("/");//3.change the directory to root
    umask(0);//4.umask
    for(int i=0;i<MAXFILE;i++) close(i);//关闭所有从父进程继承而来的打开的文件资源
    signal(SIGTERM,sigterm_handler);
    while(_running)
    {
       if((fd=open("/tmp/daemon.log",O_CREAT|O_WRONLY|O_APPEND,0600))<0)
       {
         perror("open");
         exit(1);
       }
       write(fd,buf,len+1);
       usleep(10*1000);
    }

    return 0;
}
