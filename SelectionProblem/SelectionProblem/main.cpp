#pragma once
#include <stdio.h>
#include <iostream>
using namespace std;
#include <time.h>
#include "Person.h"

#define MAXSIZE 40

void getPersons(Person*** Arr, int& size);
bool PersonIsValid(Person** Arr, int& size, int& id,char* str);
void exitProgram(Person** Arr, int& size);
bool nameNOTvalid(char* str);
int Select(Person** Arr, int left, int right, int i,int& NumComp);
const Person& RandSelection(Person** Arr, int& index, int& NumComp,int& PersonsSize);
int Partition(Person** Arr, int left, int right, int& NumComp);
void swap(Person** p1, Person** p2);

int main()
{
	Person** PersonsArr;
	const Person* ThePerson;
	int PersonsSize = 0, index, NumComp = 0;
	getPersons(&PersonsArr, PersonsSize);

	cout << "enter index: " << endl; // for testing
	cin >> index;
	if (index < 1 || index > PersonsSize)
		exitProgram(PersonsArr, PersonsSize); // invalid index

	
	ThePerson = &RandSelection(PersonsArr, index, NumComp,PersonsSize);


	return 1;
}


void getPersons(Person*** Arr, int& size)
{
	int howMany, id;
	char name[MAXSIZE];
	cout << "How many persons? :" << endl; // only for testing
	cin >> howMany;
	*Arr = new Person * [howMany];

	for (int i = 0; i < howMany; i++) // creation of the arr of persons
	{
		cin >> id;
		cin.getline(name, MAXSIZE);
		if (PersonIsValid(*Arr, size, id,name)) // check for validity in id and name.
		{
			(*Arr)[i] = new Person(name, id); // create the person if he's valid
			size++; // increase the total arr
		}
	}

}

bool PersonIsValid(Person** Arr, int& size, int& id,char* str)
{
	if (id < 0)
		exitProgram(Arr, size); 

	if(!nameNOTvalid(str)) // if the name is not valid
		exitProgram(Arr, size);

	if (size == 0) // the arr of persons is empty and passed all the above tests.
		return true;

	else
	{
		for (int i = 0; i < size; i++)
		{
			if (id == Arr[i]->getID())
				exitProgram(Arr, size);
		}

	}
	return true;
}

bool nameNOTvalid(char* str)
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


void exitProgram(Person** Arr, int& size)
{
	for (int i = 0; i < size; i++)
	{
		delete Arr[i];
	}
	delete[]Arr;
	cout << "invalid input" << endl;
	exit(0);

}

const Person& RandSelection(Person** Arr, int& index, int& NumComp,int& size)
{
	int i;
	srand((unsigned)time(NULL));
	i = Select(Arr, 0, size - 1, index,NumComp);

	return *Arr[i];
}


int Select(Person** Arr, int left, int right, int i,int& NumComp)
{
	int pivot, leftPart;
	pivot = Partition(Arr, left, right, NumComp);
	leftPart = pivot - left + 1;
	if (i == leftPart)
		return pivot;

	if (i < leftPart)
		return Select(Arr, left, pivot - 1, i, NumComp);

	else
		return Select(Arr, pivot + 1, right, i - leftPart, NumComp);
}

int Partition(Person** Arr, int left, int right,int& NumComp)
{
	int pivotIndex;
	int Randpivot = left + rand() % (right+1- left); // take a random pivot.
	Person* pivot = new Person(*Arr[Randpivot]); // pick the element that will repesent the pivot in the array.
	pivotIndex = Randpivot;
	int i = left - 1; // will be before the first element in the array

	for (int j = left; j <= right; j++) // will run on all the elements in the array
	{
		if (*Arr[j] < *pivot) // if the current element is smaller than the pivot
		{
			i++;
			swap(&Arr[j], &Arr[i]);
			if (Arr[j]->getID() == pivot->getID())
				pivotIndex = j;
			else if (Arr[i]->getID() == pivot->getID())
				pivotIndex = i;

		}
		NumComp++;
	}
	swap(&Arr[i + 1], &Arr[pivotIndex]);
	delete pivot;

	return i+1;
}


void swap(Person** p1, Person** p2)
{
	Person* temp = *p1;
	*p1 = *p2;
	*p2 = temp;

}