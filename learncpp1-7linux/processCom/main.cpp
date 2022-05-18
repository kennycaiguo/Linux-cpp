#include <iostream>
#include<signal.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>


using namespace std;


void testKill()
{
    pid_t chpid;
    int status,retval;
    chpid=fork();
    if(-1==chpid)
    {
       perror("fork()");
       exit(EXIT_FAILURE);
    }
    else if(chpid==0)
    {
        puts("In Child Process");
        sleep(100);
        exit(EXIT_SUCCESS);
    }
    else
    {
        if(0==waitpid(chpid,&status,WNOHANG))
        {
            retval=kill(chpid,SIGKILL);
            if(retval)
            {
                puts("kill failed");
                perror("kill()");
                waitpid(chpid,&status,0);
            }
            else
            {
                printf("%d killed\n",chpid);
            }
        }
    }
    exit(EXIT_SUCCESS);
}

static void sig_user(int signum)
{
    if(signum==SIGUSR1)
    {
        printf("SIGUSR1 received\n");
    }
    else if(signum==SIGUSR2)
    {
        printf("SIGUSR2 received\n");
    }
    else
    {
        printf("%d recevied\n",signum);
    }
}

void testSigaction()
{
    char buf[512];
    int n;
    struct sigaction sa_user;
    sa_user.sa_flags=0;
    sa_user.sa_handler=sig_user;
    sigaction(SIGUSR1,&sa_user,NULL);
    sigaction(SIGUSR2,&sa_user,NULL);
    printf("current pid:%d\n",getpid());
    while(1)
    {
        if((n=read(STDIN_FILENO,buf,511))==-1)
        {
            if(errno==EINTR)
            {
                printf("read is interrupted by signal\n");
            }
            else
            {
                buf[n]='\0';
                printf("%d read:%s\n",n,buf);
            }
        }
    }
}


void handler(int sig)
{
    printf("Deal SIGINT %d",sig);
}
void testSigprocmask()
{
    sigset_t newmask,oldmask,pendmask;
    struct sigaction act;
    act.sa_handler=handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;
    sigaction(SIGINT,&act,0);
     sigemptyset(&newmask);
     sigaddset(&newmask,SIGINT);
     sigprocmask(SIG_BLOCK,&newmask,&oldmask);
     sleep(5);
     sigpending(&pendmask);
     if(sigismember(&pendmask,SIGINT))
     {
       printf("SIGINT pending\n");
     }
     sigprocmask(SIG_SETMASK,&oldmask,NULL);
     printf("SIGINT unblocked\n");
     sleep(5);////在这个时间段内，如果按下CTRL+c则会调用hangler

}



//自定义信号SIGINT的处理
typedef void (*signal_handler) (int);
void signal_handler_fun(int signum)
{
 printf("received signal :%d\n",signum);
}

void customSigintproc()
{
    signal(SIGINT,signal_handler_fun);
    while (1) {}
}
//管道通信例子

void sys_err(const char* perr)
{
    perror(perr);
    exit(1);
}


void testPipecom()
{
    pid_t pid;
    char buf[1024];
    int fd[2];
    char* p="pipe testing\n";

    if(pipe(fd)==-1) sys_err("pipe");
    if((pid=fork())<0)
    {
        sys_err("fork error");
    }
    else if(pid==0)
    {
        close(fd[1]);//子进程关闭管道的写端
        printf("child process is  reading:\n");
        int len=read(fd[0],buf,sizeof(buf));//子进程从管道读取数据，如果没有数据就进入阻塞状态直到有数据
        write(STDOUT_FILENO,buf,len);
        close(fd[0]);
    }
    else
    {
        close(fd[0]);//父进程改变管道的读端
        write(STDIN_FILENO,p,strlen(p));//父进程往管道里面写数据，写完后进入阻塞状态，直到数据被读取
        wait(NULL);//等待子进程来读数据
        close(fd[1]);
    }
}

//延迟10秒钟再读取管道数据
void testDelayedPipcom()
{
    pid_t pid;
    int fd[2];
    char* p="pipe testing\n";

    if(pipe(fd)==-1) sys_err("pipe");
    if((pid=fork())<0)
    {
        sys_err("fork error");
    }

    if(pid==0)
        {
            close(fd[0]);//子进程关闭管道的读端
            sleep(10);
            write(fd[1],"hello father",strlen("hello father")+1);
            exit(EXIT_SUCCESS);
        }
    close(fd[1]);//父进程关闭管道的写端
    char buf[30];
    read(fd[0],buf,30);
    printf("received data:%s\n",buf);
}
int main()
{
    //testKill();
    //testSigaction();
    //testSigprocmask();
    //customSigintproc();
    //testPipecom();
    testDelayedPipcom();
    return 0;
}
