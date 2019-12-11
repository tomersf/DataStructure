
#pragma once
#include "Square.h"

class Queue {

	int head, tail;
	int Arr_sz;
	Square** Arr;

public:
	Queue(int size);
	~Queue();
	void MakeEmpty();
	int IsEmpty();
	Square* Front();
	void EnQueue(Square* Sq);
	Square* DeQueue();
	int AddOne(int x);
	void setSize(int size);
	void changeArrsz(int sz);
	int getSize() const;
	Square* inArr(int index);

};