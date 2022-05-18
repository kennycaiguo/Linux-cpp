#include <iostream>
#include<sys/stat.h>
#include<sys/mman.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fstream>

using namespace std;


void fileNoTest()
{
    cout<<"fileno(stdin)="<<fileno(stdin)<<endl;//0
    cout<<"fileno(stout)="<<fileno(stdout)<<endl;//1
    cout<<"fileno(stderr)="<<fileno(stderr)<<endl;//2
}

void createReadonlyfile()
{
   int fd=open("./test.txt",O_RDONLY|O_CREAT);
   close(fd);
}

void creatWriteableFile()
{
    int fd=open("./testa.dat",O_RDWR|O_CREAT|O_APPEND,0777);//需要添加权限，否则不能读写
//    char info[]="hello,i am test3.txt\ni am created by linux app!!!\n";//创建的时候不要写内容否则以后不能追加内容
//    write(fd,info,strlen(info));
    close(fd);
    cout<<"done\n";
}

void readFiletest()
{
    int fd=open("./testa.dat",O_RDWR);
    char buf[256];
    int len=0;
    while ((len=read(fd,buf,256))!=0) {
        cout<<buf<<endl;
    }


    close(fd);
}
void appendtest()
{
    int fd=open("./testa.dat",O_RDWR|O_APPEND);
    char buf[]="this is the new content\n";
    write(fd,buf,strlen(buf));
    close(fd);
    cout<<"done\n";
}


void statTest()
{
    struct stat st;
    if(-1==stat("./testa.dat",&st))
    {
        cerr<<"stat failed... "<<endl;
        return;
    }

    cout<<"file length:"<<st.st_size<<endl;
    cout<<"file mod time:"<<st.st_mtime<<endl;
    cout<<"node:"<<st.st_ino<<endl;
    cout<<"mode:"<<st.st_mode<<endl;

}
void mmapTest()
{
   int fd;
   char* mapped_mem,*p;
   int flength=1024;
   void* start_addr;
   fd=open("./testa.txt",O_RDWR);
   flength=lseek(fd,1,SEEK_END);
   lseek(fd,0,SEEK_SET);
   start_addr=(void*)0x80000;
   mapped_mem=(char*)mmap(start_addr,flength,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
   printf("%s\n",mapped_mem);
   while ((p=strstr(mapped_mem,"content"))) {//find the word "content"
       memcpy(p,"Linux  ",7); //replace the word "content"
       p+=7;
   }
   close(fd);
   munmap(start_addr,flength);
}

void cppWriteFile()
{
   fstream fs("./hello.txt",ios::out|ios::app);
   fs<<"hello cpp file!!!"<<endl;
   fs.close();
}

void cppReadFile()
{
    ifstream ifs;
    ifs.open("./hello.txt");
    char content[256];
    ifs.getline(content,255);
    cout<<"content:"<<content<<endl;
    ifs.close();
}

void cppGetFileSize()
{
    long l,m;
    ifstream ifs("./testa.dat",ios::in|ios::binary);
    l=ifs.tellg();
    ifs.seekg(0,ios::end);
    m=ifs.tellg();
    long len=m-l;
    ifs.close();
    cout<<"the length of testa.dat is "<<len<<"bytes"<<endl;
}

void cppCopyFile()
{
    char* buf;
    ifstream ifs("./testa.dat",ios::in|ios::binary);
    ofstream ofs("./testacopy.dat",ios::out|ios::binary);
    //get the file size
    ifs.seekg(0,ifs.end);
    long size=ifs.tellg();
    ifs.seekg(0);
    buf=new char[size];
    ifs.read(buf,size);
    ofs.write(buf,size);
    ifs.close();
    delete[] buf;
    ofs.close();

}

void testlinkUnlink()
{
    int fd;
    struct stat st;
    //before open the file
    stat("./test.txt",&st);
    printf("1.link=%d\n",st.st_nlink);
    //after open the file
    fd=open("./test.txt",O_RDONLY);
    stat("./test.txt",&st);
    printf("2.link=%d\n",st.st_nlink);
    close(fd);
    stat("./test.txt",&st);
    printf("3.link=%d\n",st.st_nlink);
    link("./test.txt","./test2.txt");//create hard link
    stat("./test.txt",&st);
    printf("4.link=%d\n",st.st_nlink);
    unlink("./test2.txt");
    stat("./test.txt",&st);
    printf("5.link=%d\n",st.st_nlink);
    fd=open("./test.txt",O_RDONLY);
    stat("./test.txt",&st);
    printf("6.link=%d\n",st.st_nlink);
//    unlink("./test.txt");
//    stat("./test.txt",&st);
//    printf("7.link=%d\n",st.st_nlink);
    close(fd);
}
int main()
{
    //fileNoTest();
   //createReadonlyfile();
    //creatWriteableFile();
    // readFiletest();
//    appendtest();
    //statTest();
   // mmapTest();
    //cppWriteFile();
    //cppReadFile();
   // cppGetFileSize();
    //cppCopyFile();
    testlinkUnlink();
    return 0;
}
