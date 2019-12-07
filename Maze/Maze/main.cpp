#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

#define MAXLINES 25
#define MAXROWS 80
#define MINROW 1
#define MINLINE 1

void CreateMaze();
void RandomMaze();
bool ValidateHeight(int height);
bool ValidateWidth(int width);
void MakeMaze(int Height, int Width);



int main()
{

	/*srand((unsigned)time(NULL));
	int t = rand() % 4;*/
	cout << "Please select your choice: " << endl << "1 - Entering your own maze" << endl
		<< "2 - Create a random maze" << endl;
		int choice;
		cin >> choice;

		switch (choice)
		{
		case 1: 
			CreateMaze();
			break;

		case 2:
			RandomMaze();
			break;


		default:
			cout << "Invalid choice, Exiting program";
			exit(1);

		}


		return 0;
}

void CreateMaze()
{
	int Height, Width;
	bool valid;
	cout << "Please Enter your number of lines, the max is: " << MAXLINES << endl;
		cin >> Height;
		valid = ValidateHeight(Height);
		if (!valid)
		{
			cout << "Invalid input";
			exit(1);
		}

	cout << "Please Enter your number of rows, the max is: " << MAXROWS << endl;
		cin >> Width;
		valid = ValidateWidth(Width);
		if (!valid)
		{
			cout << "Invalid input";
			exit(1);
		}

	MakeMaze(Height, Width);
}


bool ValidateHeight(int height)
{
	if (height < MINROW || height > MAXROWS)
		return false;

	return true;
}

bool ValidateWidth(int width)
{
	if (width < MINLINE || width > MAXLINES)
		return false;

	return true;
}

void MakeMaze(int Height, int Width)
{
	char** Maze = new char*[Height]; // creation of the matrix
	char* row = new char[Width]; // maybe width+1 ?
	char ch;
	bool valid;
	int length;
	for (int i = 0; i < Height; i++) // loop for entering all the rows
	{
		cout << "Enter row number " << i << " as a string " << endl;
		cin.getline(row, Width);
		length = strlen(row);
		if (length != Width) // first check the size of the string, all strings need to be the same size.
		{
			cout << "Invalid input";
			exit(1);
		}
		isValidRow(row, i, Height, Width); // if row is not valid then we exit program.
		Maze[i] = new char[Width]; // make memory for the row in maze.
		strcpy(Maze[i], row); // copy the string to the row in maze.
	
	}



}

void isValidRow(char* string, int RowNum, int MaxRows, int MaxWidth)
{
	int i;
	char ch;
	for (i = 0; i < MaxWidth; i++) 
	{
		ch = string[i];
		if (ch != ' ' || ch != '*') // check for invalid chars
		{
			cout << "Invalid input";
			exit(1);
		}

		// Cases on certain rows in the maze :

		if (RowNum == 0)
		{
			for (i = 0; i < MaxWidth; i++) // will run on all the row length, char by char;
			{
				ch = string[i];
				if (ch != '*')
				{
					cout << "Invalid input";
					exit(1);
				}
			}
		}

		}


	}

	if (RowNum == 0)
	{
		for (i = 0; i < MaxWidth; i++) // will run on all the row length, char by char;
		{
			ch = string[i];
			if (ch != '*')
			{
				cout << "Invalid input";
				exit(1);
			}
		}
	}
		
	else if (RowNum == 1)
	{
		for (i = 0; i < MaxWidth; i++)
		{
			ch = string[i];
			if (i == 0)
			{
				if (ch != ' ') // (1,0) in maze has to be ' '
				{
					cout << "Invalid input";
					exit(1);
				}
			}
			else if (i == MaxWidth - 1) // wall need to be in the end of the row
			{
				if (ch != '*')
				{
					cout << "Invalid input";
					exit(1);
				}
			}
		}
	}
	else if (RowNum == MaxRows - 2) // need to be an exit from the maze
	{
		for (i = 0; i < MaxWidth; i++)
		{
			ch = string[i];
			if (i == 0)
			{
				if (ch != '*')
				{
					cout << "Invalid input";
					exit(1);
				}
			}
			else if (i == MaxWidth - 1)
			{
				if (ch != ' ')
				{
					cout << "Invalid input";
					exit(1);
				}
			}

		}
	}
	else if (RowNum == MaxRows - 1) // last row in the maze , all squares need to be *
	{
		for (i = 0; i < MaxWidth; i++)
		{
			ch = string[i];
			if (ch != '*')
			{
				cout << "Invalid input";
				exit(1);
			}

		}

	}
	else // all the rows between row 2 and row MaxRows - 2
	{
		for (i = 0; i < MaxWidth; i++)
		{
			ch = string[i];


		}

	}


	}







void cleanBuffer()
{
	char ch;
	do
	{
		ch = getchar();
	} while (ch != EOF && ch != '\n');
}