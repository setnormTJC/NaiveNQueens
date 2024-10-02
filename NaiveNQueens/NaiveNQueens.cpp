// NaiveNQueens.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

#include<iomanip>


using std::cout;
using std::string;
using std::vector;
using std::left;
using std::setw;

double factorial(int N)
{
	double result = 1;
	for (int i = N; i > 0; i--)
	{
		result *= i;
	}

	return result;
}

/*see https://cs.stackexchange.com/questions/152328/n-queens-problem-number-of-possible-placements*/
double getNumberOfWaysToPlaceNObjects_OnNxNGrid(int N)
{
	double numerator = factorial(pow(N, 2));
	double denominator = factorial(pow(N, 2) - N);

	return numerator / denominator;
}


/*
@param - chessboard MUST be square dimension (rowCount == colCount)
*/
void printChessBoard(const vector<vector<string>>& chessboard)
{
	for (auto& row : chessboard)
	{
		for (auto& character : row)
		{
			cout << left << setw(3) << character;
		}

		cout << "\n";
	}
}

/*
@param - chessboard MUST be square dimension (rowCount == colCount)
*/
void reinitializeBoard(vector<vector<string>>& chessboard)
{
	for (auto& row : chessboard)
	{
		for (auto& character : row)
		{
			character = "_";
		}
	}
}

struct Position
{
	int row;
	int column;
};

bool areQueensOnSameDiagonal(vector<Position> positions)
{
	//NOW make sure now two queens are on diagonal ...
	//https://developers.google.com/optimization/cp/queens

	//one of the following conditions must be true:

	//1) The row number PLUS the column number for each of the two queens are equal
	//	[ascending diagonal] -> from left to right 
	//OR 
	//2) The row number MINUS the column number for each of the two queens are equal.
	//	[descending diagonal] -> again, from left to right 

	for (int i = 0; i < positions.size(); ++i)
	{
		for (int j = i + 1; j < positions.size(); ++j)
		{
			if (std::abs(positions[i].row - positions[j].row) == std::abs(positions[i].column - positions[j].column))
			{
				return true;
			}
		}
	}

	return false;
}

auto generateNQueensGrids(vector<vector<string>>& chessboard)
{
	vector<vector<vector<string>>> nQueensBoardsList;

	int numberOfPossibleBoards = 0;

	for (int Q1 = 0; Q1 < chessboard.size(); Q1++)
	{
		for (int Q2 = 0; Q2 < chessboard.size(); Q2++) 
		{
			if (Q1 == Q2)
			{
				continue;
			}

			for (int Q3 = 0; Q3 < chessboard.size(); Q3++)
			{
				if (Q1 == Q3 || Q2 == Q3)
				{
					continue;
				}
				for (int Q4 = 0; Q4 < chessboard.size(); Q4++)  
					//N(N-1)(N-2)...1 = N! loop iters
				{
					if (Q1 == Q4 || Q2 == Q4 || Q3 == Q4)
					{
						continue;
					}
					//for 5 queens 
					for (int Q5 = 0; Q5 < chessboard.size(); Q5++)
					{
						if (Q1 == Q5 || Q2 == Q5 || Q3 == Q5 || Q4 == Q5)
						{
							continue; 
						}

						vector<Position> positions =
						{
							{0, Q1},
							{1, Q2},
							{2, Q3},
							{3, Q4}, 
							{4, Q5}
						};

						if (areQueensOnSameDiagonal(positions)) {
							continue;
						}

						chessboard[0][Q1] = "Q1"; //NOTE - earlier version of this prog. had Q1
						chessboard[1][Q2] = "Q2";//"Q2"
						chessboard[2][Q3] = "Q3";//"Q3"
						chessboard[3][Q4] = "Q4";//etc.
						chessboard[4][Q5] = "Q5";

						numberOfPossibleBoards++;

						nQueensBoardsList.push_back(chessboard);

					}
					reinitializeBoard(chessboard);

				}
			}
		}
	}

	return nQueensBoardsList;
}

int main()
{
	//
	const int N = 5;

	vector<vector<string>> chessboard;
	//using string instead of char because
	// Q(ueen)1, Q2, Q3 WERE put in matrix in EARLIER version of this program 

	/*initialize board with blank spaces (underscores)*/
	for (int i = 0; i < N; i++)
	{
		vector<string> currentRow;
		for (int j = 0; j < N; j++)
		{
			currentRow.push_back("_"); //filler character - underscore 
		}
		chessboard.push_back(currentRow);
	}

	printChessBoard(chessboard);

	cout << "The number of ways to place " << N << " INDISTINGUISHABLE queens on an "
		<< N << " x " << N
		<< " grid is: " << getNumberOfWaysToPlaceNObjects_OnNxNGrid(N) << "\n";

	//cout << "\n\nThe possible grids with no two queens in same row OR same column\n\n";
	auto nQueensBoardsList =
		generateNQueensGrids(chessboard);

	cout << "\n\nNumber of boards without queens on same row or column for N = "
		<< chessboard.size() << ": " << nQueensBoardsList.size() << "\n";
	cout << "COINCIDENTALLY, N! = " << factorial(chessboard.size()) << "\n";
	cout << "\n\n\n";

	cout << "These " << nQueensBoardsList.size() << " boards are: \n";
	for (auto& currentBoard : nQueensBoardsList)
	{
		printChessBoard(currentBoard);
		cout << "\n\n";
	}

	//boardsWithNoTwoQueensOnSameRowOrColumn[1]
}
