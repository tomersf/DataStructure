
#pragma once


class Square {

	int row, col;
	
public:

	Square() = default;
	Square(int row, int col);
	~Square();


	char getData();
	
	int getRow();
	int getCol();

};