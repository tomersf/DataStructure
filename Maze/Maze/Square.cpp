#include "Square.h"


Square::Square(int row, int col)
{
	this->row = row;
	this->col = col;
}


int Square::getRow()
{
	return (this->row);
}

int Square::getCol()
{
	return (this->col);
}