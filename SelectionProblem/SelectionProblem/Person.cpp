#include "Person.h"


Person::Person(char* str, int id) : id(id) // constructur
{
	name = strdup(str);
}

Person::~Person() // destructor
{
	delete name;
}

int Person::getID()
{
	return id;
}

