#pragma once
#include <stdio.h>
#include <iostream>
using namespace std;
#include <time.h>
#include "System.h"
#include "Heap.h"


void getPersons(Person*** Arr, int& size);
int Select(Person** Arr, int left, int right, int i, int& NumComp);
const Person& RandSelection(Person** Arr, int& index, int& NumComp, int& PersonsSize);
int Partition(Person** Arr, int left, int right, int& NumComp);
void CopyOriginalArr(Person** RandomArr, Person** HeapArr, Person** TreeArr);
