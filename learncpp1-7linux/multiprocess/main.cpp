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

void showPidlength()
{
    pid_t pid;
    cout<<"size of pid:"<<sizeof(pid)<<endl;//4 32bit integer

}

void testGetPid()
{
    pid_t pid=getpid();
    cout<<"pid:"<<pid<<endl;
}

static char* starter_pid_file_default="/var/run/test.pid";

static bool check_pid(char* pid_file)
{
   struct stat stb;
   FILE* pidfile;
  if(stat(pid_file,&stb)==0)
  {
     pidfile=fopen(pid_file,"r");
     if(pidfile)
      {
         char buf[64];
        pid_t pid=0;
        memset(buf,0,sizeof(buf));
       if(fread(buf,1,sizeof(buf),pidfile))
        {
           buf[sizeof(buf)-1]='\0';
           pid=atoi(buf);
        }
        fclose(pidfile);
        if(pid && kill(pid,0)==0)
        {
           return 1;
        }
      }
     printf("removing pidfile '%s',process not running",pid_file);
     unlink(pid_file);
  }
  return 0;
}

void processOpTestWithpid()
{
    FILE *fd=fopen(starter_pid_file_default,"w");
    if(fd)
    {
       fprintf(fd,"%u\n",getpid());
       fclose(fd);
    }
   if(check_pid(starter_pid_file_default))
   {
     printf("test is already running(%s exists)\n",starter_pid_file_default);
   }
   else
   {
      printf("test is Not running(%s Not exists)\n",starter_pid_file_default);
   }
    unlink(starter_pid_file_default);

}

void forkTest()
{
    pid_t fpid=0;
    int count=0;
    fpid=fork();
    if(fpid<0)
    {
       cout<<"fork()failed"<<endl;
    }
    else if(fpid==0)
    {
      cout<<"i am the child process,my pid is:"<< getpid()<<endl;
      count++;
    }
    else
    {
      cout<<"I am the parent Process,my pid is:"<<getpid()<<endl;
      cout<<"fpid:"<<fpid<<endl;
    }
    printf("result: %d\n",count);
}

void execlTest()
{
  execl("/bin/pwd","pwd",NULL);

}
void execlTestwithparam()
{

    execl("/bin/ls","ls","-al","/etc/passwd",NULL);
}

void execlTestStartMyApp()
{
    execl("/home/kenny/myapp.out",NULL);
    cout<<"================================"<<endl;//if execl success,this won't show
}

void execlpTest()
{
   // execlp("pwd","",NULL);//调用系统的程序
     execlp("/home/kenny/myapp.out",NULL);//调用自己的程序
}

void createProcessWithsystem()//使用system创建进程
{
    system("echo hello world >>msg.txt");
}


int main()
{
    //showPidlength();
    //testGetPid();
    //processOpTestWithpid();
    //forkTest();
    //execlTest();
    //execlTestwithparam();
    //execlTestStartMyApp();
   // execlpTest();
    createProcessWithsystem();
    return 0;
}
