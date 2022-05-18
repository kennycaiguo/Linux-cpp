#include<iostream>
#include"Person.h"
using namespace std;
/*
 c++ convert int to string use std::to_string(int val)
*/
void testPerson(){
	Person p1("Jack",20);
	Person p2("Jackline",25);
  cout<<p1<<endl;
  cout<<p2<<endl;
  cout.setf(ios_base::boolalpha);
	cout<<"jack is older? :"<<(p1>p2)<<endl;
}
int main()
{
  //cout<<"hello ubuntu18!!!"<<endl;
  testPerson();
  cin.get();
  return 0;
}
