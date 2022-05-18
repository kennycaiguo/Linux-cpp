#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include<string.h>
#include<time.h>

using namespace std;



int main()
{
    pid_t pc;
       int i, j, fd, len;
       int dtablesize;
       time_t t;

       /* Step 1 */
       pc = fork();
       if (pc < 0) {
           perror("fork error");
           exit(1);
       } else if (pc > 0) {
           exit(0);
       }

       /* Step 2 */
       setsid();

       /* Step 3 */
       pc = fork();
       if (pc < 0) {
           perror("fork error");
           exit(2);
       } else if (pc > 0) {
           exit(0);
       }

       /* Step 4 */
       chdir("/");

       /* Step 5 */
       umask(0);

       /* Step 6 */
       dtablesize = getdtablesize();
       for (i = 0; i < dtablesize; i++)
           close(i);

       /* Step 7 */
       signal(SIGCHLD, SIG_IGN);

       /* Done. Do the works */
       while (1) {
           sleep(60);
           if((fd=open("/tmp/mylog.txt",O_CREAT|O_WRONLY|O_APPEND,0755)>0))
           {
             t=time(0);
             char buf[256];
             sprintf(buf,"hello,the time is: %s\n",asctime(localtime(&t)));
             write(fd,buf,strlen(buf));
             close(fd);
           }
       }

       return 0;
}
