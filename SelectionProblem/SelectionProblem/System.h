#pragma onde
#include "Person.h"
#define MAXSIZE 50
#define maxNAMEsize 40
#define IDSIZE 10




class System
{
	Person** PersonsArr;
	int PersonsSize = 0;

public:

	Person**& getPersonsArr();
	int& getPersonsSize();
	bool PersonsIsValid(int& id, char* str);
	void exitProgram();
	bool nameNOTvalid(char* str) const;
	void swap(Person** p1, Person** p2);
	void cleanBuffer();
	void ExtractDetails(const char* Person, int& id, char* name);
	~System();
};

