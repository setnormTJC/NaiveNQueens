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

long long factorial(int N)
{
	long long result = 1;
	for (int i = N; i > 0; i--)
	{
		result *= i;
	}

	return result;
}

/*see https://cs.stackexchange.com/questions/152328/n-queens-problem-number-of-possible-placements*/
long long getNumberOfWaysToPlaceNObjects_OnNxNGrid(int N)
{
	long long numerator = factorial(pow(N, 2));
	long long denominator = factorial(pow(N, 2) - N);

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

auto generateGrids_WithNoTwoQueensOnSameRowOrColumn(vector<vector<string>>& chessboard)
{
	vector<vector<vector<string>>> boardsWithNoTwoQueensOnSameRowOrColumn;

	int numberOfPossibleBoards = 0;

	/*make all possible boards with no two queens in same loc*/
	for (int Q1 = 0; Q1 < chessboard.size(); Q1++)
	{
		for (int Q2 = 0; Q2 < chessboard.size(); Q2++) //Q2 excluded from column 0 (because Q1 is there) 
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
				for (int Q4 = 0; Q4 < chessboard.size(); Q4++) //Q4 will ONLY go in 4th column 
					//N(N-1)(N-2)...1 = N! loop iters
				{
					if (Q1 == Q4 || Q2 == Q4 || Q3 == Q4)
					{
						continue;
					}

					vector<Position> positions =
					{
						{0, Q1},
						{1, Q2},
						{2, Q3},
						{3, Q4}
					};

					if (areQueensOnSameDiagonal(positions)) {
						continue;
					}

					chessboard[0][Q1] = "Q"; //NOTE - earlier version of this prog. had Q1
					chessboard[1][Q2] = "Q";//"Q2"
					chessboard[2][Q3] = "Q";//"Q3"
					chessboard[3][Q4] = "Q";//etc.

					numberOfPossibleBoards++;

					boardsWithNoTwoQueensOnSameRowOrColumn.push_back(chessboard);

					//printChessBoard(chessboard);

					//cout << "Next possible board ...\n\n\n";
					//system("pause"); 
					reinitializeBoard(chessboard);

				}
			}
		}
	}

	return boardsWithNoTwoQueensOnSameRowOrColumn;
}



auto removeDiagonals(vector<vector<vector<string>>> boardsWithNoTwoQueensOnSameRowOrColumn)
{
	vector<vector<vector<string>>> boardsThatSatisfyNQueens;


	for (auto& currentBoard : boardsWithNoTwoQueensOnSameRowOrColumn)
	{
		bool doesBoardSatisfyNQueens = false;

		//check if any two queens are on diagonal ...
		//https://developers.google.com/optimization/cp/queens

		//one of the following conditions must be true:

		//1) The row number PLUS the column number for each of the two queens are equal
		//	[ascending diagonal] -> from left to right 
		//OR 
		//2) The row number MINUS the column number for each of the two queens are equal.
		//	[descending diagonal] -> again, from left to right 

		//vector<Position> queenPositions; 
		//std::find

		if (doesBoardSatisfyNQueens)
		{
			boardsThatSatisfyNQueens.push_back(currentBoard);
		}
	}
	return boardsThatSatisfyNQueens;
}

int main()
{
	//
	const int N = 4;

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
	auto boardsWithNoTwoQueensOnSameRowOrColumn =
		generateGrids_WithNoTwoQueensOnSameRowOrColumn(chessboard);

	cout << "\n\nNumber of boards without queens on same row or column for N = "
		<< chessboard.size() << ": " << boardsWithNoTwoQueensOnSameRowOrColumn.size() << "\n";
	cout << "COINCIDENTALLY, N! = " << factorial(chessboard.size()) << "\n";
	cout << "\n\n\n";

	cout << "These " << boardsWithNoTwoQueensOnSameRowOrColumn.size() << " boards are: \n";
	for (auto& currentBoard : boardsWithNoTwoQueensOnSameRowOrColumn)
	{
		printChessBoard(currentBoard);
		cout << "\n\n";
	}

	//boardsWithNoTwoQueensOnSameRowOrColumn[1]
}
