/*
 * Person.h
 *
 *  Created on: May 5, 2022
 *      Author: kenny
 */
#include<string>
using namespace std;

#ifndef PERSON_H_
#define PERSON_H_

class Person {
public:
	string name;
	int age;
public:
	Person();
	Person(string name,int age);
	virtual ~Person();
	friend ostream& operator<<(ostream& os,const Person& p);
	bool operator>(const Person& p);
};

#endif /* PERSON_H_ */
