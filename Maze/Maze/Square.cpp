#include "Square.h"


Square::Square(char data, int row, int col)
{
	this->data = data;
	this->row = row;
	this->col = col;
}



void Square:: changeData(char data)
{
	this->data = data;
}

char Square::getData()
{
	return (this->data);
}

int Square::getRow()
{
	return (this->row);
}

int Square::getCol()
{
	return (this->col);
}