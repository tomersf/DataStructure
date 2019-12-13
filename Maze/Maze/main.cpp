#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "Square.h"
#include "Queue.h"
#include "Stack.h"


using namespace std;
#pragma warning(disable : 4996)

#define MAXROWS 25
#define MAXCOLS 80
#define MINROWS 3
#define MINCOLS 1

void getDimensions(int choice);
void RandomMaze(int& height,int& width);
bool ValidateHeight(int& height);
bool ValidateWidth(int& width);
void MakeMaze(int& Height, int& Width);
void isValidRow(char* string, int& RowNum, int& MaxRows, int& MaxWidth);
void printMaze(char** maze, int& rows, int& cols);
void cleanBuffer(int& i);
void SolveMaze(char** Maze, int& Height, int& Width);
bool NotInQueue(Queue* Q, int row, int col);
void MakeRandomMaze(char** Maze, int& Height, int& Width);
bool HasUnvisitedNeighbors(Square* sq, char** Maze, Square*& Neighbor, int& Height, int& Width);



int main()
{
	/*cout << "Please select your choice: " << endl << "1 - Entering your own maze" << endl
		<< "2 - Create a random maze" << endl;*/
	cout << "Maze: 1) From input 2) Random" << endl;
		int choice;
		cin >> choice;

		switch (choice)
		{
		case 1: 
			getDimensions(choice);
			break;

		case 2:
			getDimensions(choice);
			break;

		default:
			cout << "Invalid choice, Exiting program";
			exit(1);

		}

		return 0;
}

void getDimensions(int choice)
{
	int Height, Width;
	bool valid;
	/*cout << "Please Enter your number of rows, the max is: " << MAXROWS << endl;*/
		cin >> Height;
		valid = ValidateHeight(Height);
		if (!valid)
		{
			cout << "Invalid input";
			exit(1);
		}

	/*cout << "Please Enter your number of columns, the max is: " << MAXCOLS << endl;*/
		cin >> Width;
		valid = ValidateWidth(Width);
		if (!valid)
		{
			cout << "Invalid input";
			exit(1);
		}

		if (choice == 1)
			MakeMaze(Height, Width);
		else
			RandomMaze(Height, Width);

}


bool ValidateHeight(int& height)
{
	if (height < MINROWS || height > MAXROWS)
		return false;

	return true;
}

bool ValidateWidth(int& width)
{
	if (width < MINCOLS || width > MAXCOLS)
		return false;

	return true;
}

void MakeMaze(int& Height, int& Width)
{
	char** Maze = new char*[Height]; // creation of the matrix
	char* row = new char[Width];
	int length;
	for (int i = 0; i < Height; i++) // loop for entering all the rows
	{
		/*cout << "Enter row number " << i+1 << " as a string " << endl;*/
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

	SolveMaze(Maze, Height, Width);
}

void SolveMaze(char** Maze, int& Height, int& Width)
{
	Queue Queue((Height * Width) - ((2 * Width))); // reducing the first row and last row(borders)
	Queue.setSize(((Height * Width) - ((2 * Width))));

	if (Queue.getSize() == 1) // Special case of maze 3x1
	{
		Maze[1][0] = '$';
		printMaze(Maze, Height, Width);
		return;
	}

	Square* Sq = new Square(1,0); // initialize the starting index's of the maze 
	Queue.EnQueue(Sq); // initialize the queue with square (1,0)
	
	while(!(Queue.IsEmpty())) // while the queue is not empty
	{
		Sq = Queue.DeQueue();  
		Maze[Sq->getRow()][Sq->getCol()] = '$'; // mark as visited
		if (Sq->getRow() == Height - 2 && Sq->getCol() == Width - 1) // meaning we are at exit point
		     break;

			Square* Up, * Down, * Right, * Left;
			if (Maze[Sq->getRow()][Sq->getCol() + 1] == ' ') // Right Square of current square
			{
				if (NotInQueue(&Queue,Sq->getRow(),Sq->getCol()+1))
				{
					Right = new Square(Sq->getRow(), Sq->getCol() + 1);
					Queue.EnQueue(Right);
				}
				
			}
			if (Maze[Sq->getRow() + 1][Sq->getCol()] == ' ') // Below square of current square
			{
				if (NotInQueue(&Queue,Sq->getRow() + 1, Sq->getCol()))
				{
					Down = new Square(Sq->getRow() + 1, Sq->getCol());
					Queue.EnQueue(Down);
				}
				
			}
			if (Maze[Sq->getRow()][Sq->getCol() - 1] == ' ') // Left square of current square
			{
				if (NotInQueue(&Queue, Sq->getRow(),Sq->getCol() - 1))
				{
					Left = new Square(Sq->getRow(), Sq->getCol() - 1);
					Queue.EnQueue(Left);
				}
				
			}
			if (Maze[Sq->getRow() - 1][Sq->getCol()] == ' ') // Above square of current square
			{
				if (NotInQueue(&Queue, Sq->getRow() - 1, Sq->getCol()))
				{
					Up = new Square(Sq->getRow() - 1, Sq->getCol());
					Queue.EnQueue(Up);
				}
				
			}
	}

	if (Maze[Height - 2][Width - 1] != '$') // checking to see if we solved the maze.
	{
		cout << "no solution";
		return;
	}

	printMaze(Maze, Height, Width);
}

bool NotInQueue(Queue* Q,int row,int col)
{
	if (!(Q->IsEmpty()))
	{
		for (int i = 0; i < Q->getSize(); i++)
		{
			if (Q->inArr(i) != nullptr)
			{
				if (Q->inArr(i)->getRow() == row && Q->inArr(i)->getCol() == col)
					return false;

			}
		}
	}
	
	return true;
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

void RandomMaze(int& Height, int& Width)
{
	char** Maze = new char* [Height];
	for (int i = 0; i < Height; i++)
	{
		Maze[i] = new char[Width];
		for (int j = 0; j < Width; j++)
		{
			if (i == 1 && j==0) // Entry of the maze
				Maze[i][j] = '$';
		
			else if (i == Height - 2 && j == Width - 1) // Exit of maze
				Maze[i][j] = ' ';
			

			else // All other squares will be *
			Maze[i][j] = '*';
		}
	}
	MakeRandomMaze(Maze, Height, Width);
}

void MakeRandomMaze(char** Maze, int& Height, int& Width)
{
	srand((unsigned)time(NULL));
	int row = 1, col = 1;
	Square* sq = new Square(row, col);
	Stack stack(sq);

	while (!(stack.IsEmpty())) // while the stack is not empty
	{
		Square* temp = stack.Pop();
		Square* Neighbor;
		Maze[temp->getRow()][temp->getCol()] = '$'; // mark as visited 
		if (temp->getRow() == Height - 2 && temp->getCol() == Width - 1) // Meaning we are at exit point
			break;

		if (HasUnvisitedNeighbors(temp, Maze,Neighbor,Height,Width))
		{
			stack.Push(temp);
			stack.Push(Neighbor);
		}
	}

	if (Maze[Height - 2][Width - 1] != '$') // checking to see if we solved the maze.
	{
		cout << "no solution";
		return;
	}
	printMaze(Maze, Height, Width);
}

bool HasUnvisitedNeighbors(Square* sq, char** Maze, Square*& Neighbor,int& Height,int& Width)
{
	int CurrentRow = sq->getRow();
	int	CurrentCol = sq->getCol();

	if (Height == 3) // Maze of 3 rows, can only go right.
	{
		if (Maze[CurrentRow][CurrentCol + 1] == '*' || Maze[CurrentRow][CurrentCol + 1] == ' ')
		{
			Maze[CurrentRow][CurrentCol + 1] = '$';
			Neighbor = new Square(CurrentRow, CurrentCol + 1);
			return true;
		}
	}
	else // Maze have more then 3 rows
	{
		Square** Neighbors = new Square * [4]; // max size of 4
		int counter = 0;
		 
		//Right Neighbor:
		if (CurrentCol + 1 != Width - 1) // Check if the right neighbor is on the right border of maze.
		{
			if (Maze[CurrentRow][CurrentCol + 1] == '*' || Maze[CurrentRow][CurrentCol + 1] == ' ')
			{
				Neighbors[counter] = new Square(CurrentRow, CurrentCol + 1);
				counter++;
			}
		}

		if (CurrentCol + 1 == Width - 1 && CurrentRow == Height - 2) // if the Right neighbor is the exit of the maze
		{
			Neighbors[counter] = new Square(CurrentRow, CurrentCol + 1);
			counter++;

		}

		//Below Neighbor:
		if (CurrentRow + 1 != Height - 1)// Check if the below neighbor is on the bottom border of maze.
		{
			if (Maze[CurrentRow + 1][CurrentCol] == '*')
			{
				Neighbors[counter] = new Square(CurrentRow + 1, CurrentCol);
				counter++;

			}

		}

		//Left Neighbor:
		if (CurrentCol - 1 != 0) // Check if the left neighbor is on the left border of maze.
		{
			if (Maze[CurrentRow][CurrentCol - 1] == '*')
			{
				Neighbors[counter] = new Square(CurrentRow, CurrentCol - 1);
				counter++;
			}

		}
		
		//Above Neighbor:
		if (CurrentRow - 1 != 0) // Check if the above neighbor is on the top border of maze.
		{
			if (Maze[CurrentRow - 1][CurrentCol] == '*')
			{
				Neighbors[counter] = new Square(CurrentRow - 1, CurrentCol);
				counter++;
			}
		}
		if (counter > 0)
		{
			int i = rand() % counter; // choose a rand neighbor
			Neighbor = new Square (Neighbors[i]->getRow(),Neighbors[i]->getCol());

			for (int j = 0; j < counter; j++) // clear space, no need for the neighbors anymore.
			{
				delete Neighbors[j];
			}
			delete[] Neighbors;
			return true;
		}
	}
	return false;
}