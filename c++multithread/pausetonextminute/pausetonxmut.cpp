//暂停线程到下一分钟
#include<iostream>
#include<thread>
#include<chrono>
#include<ctime>
#include<time.h>
#include<stddef.h>

using namespace std;

void getNowTime()
{
  timespec time;
  struct tm nowTime;
  
  clock_gettime(CLOCK_REALTIME,&time);//获取从1970到现在的秒数
  localtime_r(&time.tv_sec,&nowTime);
  char current[1024];
  printf(
       "%04d-%02d-%02d %02d:%02d:%02d\n",
	   nowTime.tm_year+1900,
       nowTime.tm_mon+1,
       nowTime.tm_mday,	
       nowTime.tm_hour,	   
	   nowTime.tm_min,
	   nowTime.tm_sec);
}

int main()
{
  using chrono::system_clock;
  time_t tt=system_clock::to_time_t(system_clock::now());
  struct tm *ptm = localtime(&tt);
  getNowTime();//获取并且输出当前时间
  cout<<"Waiting for the next mimute to begin...\n";
  ++ptm->tm_min;//累加一分钟
  ptm->tm_sec=0;//秒数置0
  
  this_thread::sleep_until(system_clock::from_time_t(mktime(ptm)));//暂停执行到下一整分时间
  getNowTime();//获取并且输出当前时间
  
  return 0;
}
