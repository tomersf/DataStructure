#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "Square.h"
#include "Queue.h"


using namespace std;
#pragma warning(disable : 4996)

#define MAXLINES 25
#define MAXROWS 80
#define MINROW 1
#define MINLINE 1

void CreateMaze();
//void RandomMaze();
bool ValidateHeight(int& height);
bool ValidateWidth(int& width);
void MakeMaze(int& Height, int& Width);
void isValidRow(char* string, int& RowNum, int& MaxRows, int& MaxWidth);
void printMaze(char** maze, int& rows, int& cols);
void cleanBuffer(int& i);
void SolveMaze(char** Maze, int& Height, int& Width);



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
			/*RandomMaze();
			break;*/


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

		if (Height != Width)
		{
			cout << "Invalid input";
			exit(1);
		}

	MakeMaze(Height, Width);
}


bool ValidateHeight(int& height)
{
	if (height < MINROW || height > MAXROWS)
		return false;

	return true;
}

bool ValidateWidth(int& width)
{
	if (width < MINLINE || width > MAXLINES)
		return false;

	return true;
}

void MakeMaze(int& Height, int& Width)
{
	char** Maze = new char*[Height]; // creation of the matrix
	char* row = new char[Width+1];
	int length;
	for (int i = 0; i < Height; i++) // loop for entering all the rows
	{
		cout << "Enter row number " << i+1 << " as a string " << endl;
		cleanBuffer(i);
		cin.getline(row, Width+1);
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
	cout << endl;
	printMaze(Maze,Height,Width);
	cout << endl;

	SolveMaze(Maze, Height, Width);

}

void SolveMaze(char** Maze, int& Height, int& Width)
{
	int row = 1, col = 0; // initialize the starting index's of the maze 

	Queue Queue((Height * Width) - ((2 * Width)));
	Queue.setSize(((Height * Width) - ((2 * Width))));

	//if (Height != 3)
	//{
	//	Queue.changeArrsz((Height * Width) - ((2 * Width) + (2 * (Height - 2)))); // from total size we remove the limits of the maze.
	//	Queue.setSize(((Height * Width) - ((2 * Width) + (2 * (Height - 2)))));
	//}

	Square* Sq = new Square(Maze[row][col], row, col);
	Queue.EnQueue(Sq); // initialize the queue with square (1,0)
	
	while(!(Queue.IsEmpty())) // while the queue is not empty
	{
		Sq = Queue.DeQueue(); //////////////// NEED TO REMOVE THE POINTER IN THE ARRAY ? // 4x4 no exit gets thrown, need to check if no exit .
		Sq->changeData('$');
		Maze[Sq->getRow()][Sq->getCol()] = '$';
		if (Sq->getRow() == Height - 2 && Sq->getCol() == Width - 1) // meaning we are at exit point
		     break;


			Square* Up, * Down, * Right, * Left;
			if (Maze[Sq->getRow()][Sq->getCol() + 1] == ' ')
			{
				Right = new Square(Maze[Sq->getRow()][Sq->getCol() + 1], Sq->getRow(), Sq->getCol() + 1);
				Queue.EnQueue(Right);
			}
			if (Maze[Sq->getRow() + 1][Sq->getCol()] == ' ')
			{
				Down = new Square(Maze[Sq->getRow() + 1][Sq->getCol()], Sq->getRow() + 1, Sq->getCol());
				Queue.EnQueue(Down);
			}
			if (Maze[Sq->getRow()][Sq->getCol() - 1] == ' ')
			{
				Left = new Square(Maze[Sq->getRow()][Sq->getCol() - 1], Sq->getRow(), Sq->getCol() - 1);
				Queue.EnQueue(Left);
			}
			if (Maze[Sq->getRow() - 1][Sq->getCol()] == ' ')
			{
				Up = new Square(Maze[Sq->getRow() - 1][Sq->getCol()], Sq->getRow() - 1, Sq->getCol());
				Queue.EnQueue(Up);
			}

	}
	printMaze(Maze, Height, Width);
}

void cleanBuffer(int &i)
{
	if (i == 0)
	{
	  char ch;
		do
		{
			ch = getchar();
		} while (ch != EOF && ch != '\n');

	}
	
}


void isValidRow(char* string, int& RowNum, int& MaxRows, int& MaxWidth)
{
	int i;
	char ch;
	for (i = 0; i < MaxWidth; i++)
	{
		ch = string[i];

		if ((ch != ' ') && (ch != '*')) // check for invalid chars
		{
			cout << "Invalid input";
			exit(1);
		}

		// Cases on certain rows in the maze :

		if (RowNum == 0)
		{
			if (ch != '*')
			{
				cout << "Invalid input";
				exit(1);
			}

		}
		else if (MaxRows - 2 == 1 && RowNum == 1) // only 3 rows, the row in the middle need to be all spaces.
		{

			if (string[i] != ' ')
			{
				cout << "Invalid input";
				exit(1);

			}

		}
		else if (RowNum == 1)
		{
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
		else if (RowNum == MaxRows - 2) // need to be an exit from the maze
		{
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

		else if (RowNum == MaxRows - 1) // last row in the maze , all squares need to be *
		{
			if (ch != '*')
			{
				cout << "Invalid input";
				exit(1);
			}

		}

		else // all the rows between row 2 and row MaxRows - 2 , need to check for borders.
		{
			if (string[0] != '*')
			{
				cout << "Invalid input";
				exit(1);
			}

			if (string[MaxWidth - 1] != '*')
			{
				cout << "Invalid input";
				exit(1);
			}

		}
	}

}

void printMaze(char** maze, int& rows, int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << maze[i][j];
		}

		cout << endl;
	}

}