#pragma once

#include "Square.h"

class Node
{
	Square* sq;
	Node* next;

public:
	Node();
	Node(Square* sq, Node* nxt = nullptr);
	

	friend class Stack;
};