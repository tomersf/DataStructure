#include "Queue.h"
#include <iostream>
using namespace std;


Queue::Queue(int size)
{
	head = 1;
	tail = 0;
	Arr_sz = size;
	Arr = new Square* [size];
	for (int i = 0; i < size;i++)
	{
		Arr[i] = nullptr;
	}
	
}

Queue::~Queue()
{
	for (int i = 0; i < Arr_sz; i++)
	{
		if(Arr[i]!= nullptr)
		   delete[] Arr[i];
	}
	if(Arr != nullptr)
	   delete Arr;
}

void Queue::MakeEmpty()
{
	for (int i = 0; i < Arr_sz;i++)
	{
		delete Arr[i];
		Arr[i] = nullptr;
	}

	Arr = nullptr;
	head = 1;
	tail = 0;
}

int Queue::AddOne(int x)
{

	return((1 + x) % Arr_sz);
}

int Queue::IsEmpty()
{

	return(AddOne(tail) == head);
}

Square* Queue::Front()
{
	if (IsEmpty())
	{
		cout << "ERROR: Queue is empty \n";
		exit(1);
	}

	return (Arr[head]);
}

void Queue::setSize(int size)
{
	Arr_sz = size;
}

void Queue::changeArrsz(int sz)
{
	delete[]Arr;

	Arr = new Square * [sz];
}

void Queue::EnQueue(Square* sq)
{
	if (AddOne(AddOne(tail)) == head)
	{
		cout << "Error: Queue is Full \n"; 
		exit(1);
	}
		
	/*Arr[tail] = new Square();*/
	tail = AddOne(tail);
	Arr[tail] = sq;

}

Square* Queue::DeQueue()
{
	if (IsEmpty())
	{
		cout << "ERROR: Queue is empty \n";
		exit(1);
	}


	Square* temp = Arr[head];
	/*Arr[head] = nullptr;*/
	head = AddOne(head);
	return (temp);
}

Square* Queue::inArr(int index)
{
	return Arr[index];
}

int Queue::getSize() const
{
	return Arr_sz;
}