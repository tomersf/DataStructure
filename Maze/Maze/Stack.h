#pragma once
#include "Square.h"
#include "Node.h"


class Stack
{
	Node* head = nullptr; // point to start of the stack
	
public:
	Stack(Square* sq);
	~Stack();
	bool IsEmpty();
	void MakeEmpty();
	void Push(Square* sq);
	Square* Pop();

};