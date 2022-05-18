#include "person.h"

Person::Person()
{

}

Person::Person(string name,int age)
{
   this->name=name;
   this->age=age;
}

ostream& operator<<(ostream& os,const Person p)
{
    os<<string("Person[name:")<<p.name<<string(",age:")<<to_string(p.age)<<string("]\n");
    return os;
}

Person& Person::operator=(const Person& p)
{
    this->name = p.name;
    this->age = p.age;
    return *this;
}

bool Person::operator==(const Person& p)
{
    return this->name==p.name && this->age==p.age;
}

bool Person::operator>(const Person& p)
{
    return this->age > p.age;
}
