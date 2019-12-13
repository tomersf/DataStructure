#include "Stack.h"
#include <iostream>
using namespace std;

Stack::Stack(Square* sq)
{
	if (head == nullptr)
	{
		head = new Node(sq, nullptr);
	}
	else
		Push(sq);
}

Stack::~Stack()
{
	MakeEmpty();
}

bool Stack::IsEmpty()
{
	return(head == nullptr);
}

void Stack::MakeEmpty()
{
	Node* temp;
	while (head != nullptr)
	{
		temp = head;
		head = head->next;
		delete temp->sq;
		delete temp;
	}
}

void Stack::Push(Square* sq)
{
	head = new Node(sq, head);
}

Square* Stack::Pop()
{
	if (IsEmpty())
	{
		cout << "Unable to pop, stack is empty";
		exit(1);
	}
	Node* temp = head;
	Square* sq = head->sq;
	head = head->next;
	delete temp;
	return (sq);
}