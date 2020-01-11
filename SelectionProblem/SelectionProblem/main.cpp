#pragma once
#include "main.h"


System TheSystem; // global system
int main()
{
	Person** PersonsArr = nullptr;
	const Person* ThePerson;
	int* PersonsSize = &TheSystem.getPersonsSize();
	int index, NumComp = 0;
	
	getPersons(&PersonsArr, *PersonsSize);
	cout << "enter index: " << endl; // for testing
	cin >> index;
	if (index < 1 || index > *PersonsSize)
		TheSystem.exitProgram(); // invalid index

	Person** SelectionArr = nullptr, ** HeapArr=nullptr, ** TreeArr=nullptr;
	CopyOriginalArr(SelectionArr, HeapArr, TreeArr);
	

	ThePerson = &RandSelection(PersonsArr, index, NumComp,*PersonsSize);
	//ThePerson = &selectHeap(PersonsArr, index, NumComp, PersonsSize);



	return 1;
}


void getPersons(Person*** Arr, int& size)
{
	int howMany;
	char PersonDetails[MAXSIZE]; // full name with id
	char name[MAXSIZE]; // only the name
	int id = -1;
	cout << "How many persons? :" << endl; // only for testing
	cin >> howMany;
	*Arr = new Person * [howMany];
	TheSystem.getPersonsArr() = *Arr;

	for (int i = 0; i < howMany; i++) // creation of the arr of persons
	{
		if(i==0)
		 TheSystem.cleanBuffer();
		cin.getline(PersonDetails, MAXSIZE); // get the details of the person(id + full name)
		TheSystem.ExtractDetails(PersonDetails, id, name);
		
		if (TheSystem.PersonsIsValid(id,name)) // check for validity in id and name.
		{
			(*Arr)[i] = new Person(name, id); // create the person if he's valid
			size++;
		}
	}
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
			TheSystem.swap(&Arr[j], &Arr[i]);
			if (Arr[j]->getID() == pivot->getID())
				pivotIndex = j;
			else if (Arr[i]->getID() == pivot->getID())
				pivotIndex = i;

		}
		NumComp++; // increase the numcomp everytime we compare two persons
	}
	TheSystem.swap(&Arr[i + 1], &Arr[pivotIndex]);
	delete pivot;

	return i+1; // return the index of the pivot
}

//const Person& selectHeap(Person** Arr, int k, int& NumComp,int& size)
//{
//
//
//
//}

void CopyOriginalArr(Person** RandomArr, Person** HeapArr, Person** TreeArr)
{
	int size = TheSystem.getPersonsSize();
	Person** OriginalArr = TheSystem.getPersonsArr();
	RandomArr = new Person * [size];
	HeapArr = new Person * [size];
	TreeArr = new Person * [size];
	for (int i = 0; i <size ; i++)
	{
		RandomArr[i] = new Person(*OriginalArr[i]);
		HeapArr[i] = new Person(*OriginalArr[i]);
		TreeArr[i] = new Person(*OriginalArr[i]);
	}

}