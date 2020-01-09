
#include <string.h>
#pragma warning(disable : 4996)
using namespace std;
#include <iostream>


class Person
{
private :
	char* name;
	int id;

public:
	Person() = delete;
	Person(char* str, int id);
	const Person(const Person& other)
	{
		name = strdup(other.name);
		id = other.id;

	}
	~Person();
	Person(Person&& other)
	{
		name = other.name;
		id = other.id;
		other.name = nullptr;
	}

	bool operator<(const Person& other) const
	{
		if (id < other.id)
			return true;

		return false;
	}

	const Person& operator=(const Person& other)
	{
		if (this != &other)
		{
			id = other.id;
			delete[]name;
			name = strdup(other.name);

		}
		return *this;
	}

	

	int getID();

};