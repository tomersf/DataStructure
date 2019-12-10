
#pragma once


class Square {

	char data;
	int row, col;
	
public:

	Square() = default;
	Square(char data, int row, int col);


	char getData();
	void changeData(char data);
	int getRow();
	int getCol();

};