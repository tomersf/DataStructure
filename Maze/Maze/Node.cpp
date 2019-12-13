#include "Node.h"
#include <iostream>
using namespace std;


Node::Node() : sq()
{
	next = nullptr;
}

Node::Node(Square* sq, Node* nxt) : sq(sq), next(nxt)
{
}

