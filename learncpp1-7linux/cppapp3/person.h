#ifndef PERSON_H
#define PERSON_H
#include<string>
using namespace std;

class Person
{
public:
    Person();
    Person(string name,int age);
    friend ostream& operator <<(ostream& os,const Person p);
    bool operator >(const Person& p);
    bool operator ==(const Person& p);
    Person& operator=(const Person& p);
public:
    string name;
    int age;
};

#endif // PERSON_H
