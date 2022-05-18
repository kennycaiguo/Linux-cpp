#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<sys/sem.h>
#include<sys/stat.h>
#include<string.h>

using namespace std;

void testFtok()
{
    key_t semkey;
    if((semkey=ftok("./test.txt",123))<0)
    {
        printf("ftok failed\n");
        exit(EXIT_FAILURE);
    }
    printf("ftok ok,semkey=%d\n",semkey);
}

void ftokInsider() //解开ftok产生键值的内幕
{
    char filename[50];
    struct stat buf;
    strcpy(filename,"./test.txt");
    int ret =stat(filename,&buf);
    if(ret)
    {
      printf("stat error\n");
      return;
    }
      printf("the file info: ftok(filename,0x27)=%x,st_ino=%x,st_dev=%x\n",ftok(filename,0x27),buf.st_ino,buf.st_dev);

}
int main()
{
   //testFtok();
    ftokInsider();
    return 0;
}
