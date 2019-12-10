#include "Queue.h"
#include <iostream>
using namespace std;


Queue::Queue(int size)
{
	head = 0;
	tail = 0;
	Arr_sz = 0;
	Arr = new Square* [size];

}

Queue::~Queue()
{
	for (int i = 0; i < Arr_sz; i++)
	{
		delete[] *Arr;
	}
	delete Arr;
}

void Queue::MakeEmpty()
{
	head = 0;
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
	if (AddOne(tail) == head)
	{

		cout << "Error: Queue is Full \n"; 
		exit(1);
	}
		
	Arr[tail] = new Square();
	Arr[tail] = sq;
	tail = AddOne(tail);

}

Square* Queue::DeQueue()
{
	if (IsEmpty())
	{
		cout << "ERROR: Queue is empty \n";
		exit(1);
	}

	Square* temp = Arr[head];
	head = AddOne(head);
	return (temp);
}