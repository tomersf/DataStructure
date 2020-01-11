#include "System.h"



Person**& System::getPersonsArr()
{
	return PersonsArr;
}

int& System::getPersonsSize()
{
	return PersonsSize;
}


bool System::PersonsIsValid(int& id, char* str)
{
	if (id < 0)
		exitProgram();

	if (!nameNOTvalid(str)) // if the name is not valid
		exitProgram();

	if (PersonsSize == 0) // the arr of persons is empty and passed all the above tests.
		return true;

	else
	{
		for (int i = 0; i < PersonsSize; i++)
		{
			if (id == PersonsArr[i]->getID())
				exitProgram();
		}

	}
	return true;
}

void System:: exitProgram()
{
	for (int i = 0; i < PersonsSize; i++)
	{
		delete PersonsArr[i];
	}
	delete[]PersonsArr;
	cout << "invalid input" << endl;
	exit(0);

}

bool System:: nameNOTvalid(char* str) const
{
	int length;
	length = strlen(str);
	if (length >= MAXSIZE) // if the length of the name is larger then MAXSIZE
		return false;

	for (int i = 0; i < length; i++) // check for invalid chars in the name
	{
		char ch = str[i];
		if (ch < 'A' || (ch > 'Z' && ch < 'a') || ch > 'z') // checking if the char is in the range of chars on ASCII table.
		{
			if (ch != ' ')
				return false;
		}
	}

	return true;
}

void System::swap(Person** p1, Person** p2)
{
	Person* temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

System::~System()
{
	for (int i = 0; i < PersonsSize; i++)
		delete PersonsArr[i];
	delete[] PersonsArr;
}

void System::cleanBuffer()
{
	char ch;
	do
	{
		ch = getchar();
	} while (ch != EOF && ch != '\n');
}

void System:: ExtractDetails(const char* Person, int& id, char* name)
{
	char IDstr[IDSIZE]; // id size is max 9 digits
	int IDlength = 0, Spaces = 0;
	int length = strlen(Person);
	char ch;
	for (int i = 0; i < length; i++)
	{
		ch = Person[i];
		if ((ch - '0' < 10) && (ch - '0' >= 0)) // Extract the ID
			IDlength++;

		else if (ch == ' ')
			Spaces++;

		else if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) // when we ecounter the first letter we stop
			break;
	}
	if (IDlength == 0 || Spaces == 0) // not valid details
		exitProgram();
	memcpy(IDstr, Person, IDlength); // copy the id
	memcpy(name, Person + (IDlength + Spaces), maxNAMEsize); // copy the name
	id = atoi(IDstr); // get the actucal id

}