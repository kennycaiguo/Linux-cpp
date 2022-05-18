/*
 * Person.cpp
 *
 *  Created on: May 5, 2022
 *      Author: kenny
 */

#include "Person.h"
#include<string>
using namespace std;

Person::Person() {
	// TODO Auto-generated constructor stub

}

Person::Person(string name,int age)
{
  this->name=name;
  this->age=age;
}

Person::~Person() {
	// TODO Auto-generated destructor stub
}

ostream& operator<<(ostream& os,const Person& p)
{
	os<<p.name<<string(" ");
	os<<to_string(p.age);
	return os;
}

bool Person::operator>(const Person& p)
{
	return this->age > p.age;
}
