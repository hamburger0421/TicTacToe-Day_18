#include "ticTacToeFunctions.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <random>
#include <chrono>

void screenWiper(int screenScrollVar) //This functions scrolls the screen such that the text will be at the bottom
{
	for (int i{}; i < screenScrollVar; i++)
	{
		std::cout << "\n";
	}
} 
void startUpTextFunction() //This function is responsible for the text at the execution of the program.
{
	screenWiper(30);
	std::cout << "Welcome to Tic Tac Toe against A.I.! To proceed, type "
		"and enter \"START\" to start a game and \"RULES\" to know learn more."
		"\n-> ";
	std::string startupInput{};
	std::cin >> startupInput;
	if (startupInput == "START")
	{
		return;
	}
	else if (startupInput == "RULES")
	{
		screenWiper(30);
		std::cout << "The objective of this game is to match 3 of your tiles"
			" such that it forms a line. Type in any text to continue. \n-> ";
		std::cin >> startupInput;
		screenWiper(30);
		std::cout << "Your turn will be randomly generated, and you will face"
			" off against an A.I.. \n-> ";
		std::cin >> startupInput;
		screenWiper(30);
		std::cout << "To place a tile, pick a number between 1-9 as if in a"
			" phone keypad. Good luck, and have fun! \n-> ";
		std::cin >> startupInput;
		startUpTextFunction();
	}
	else
	{
		startUpTextFunction();
	}
}
int turnRandomizer() //This function randomizes the user's turn, whether they are going first or second.
{
	std::srand((unsigned int) time(0));
	int turn = std::rand() % 2;
	return turn;
}
void boardPrintout(int userInputInteger, char ticTacToeTiles[3][3], int turn) //This function prints the board while checking for the user's/A.I.'s inputs
{
	int column{};
	int row{};
	char functionTurn{};
	if (turn == 0)
	{
		functionTurn = 'X';
	}
	else if (turn == 1)
	{
		functionTurn = 'O';
	}

	if (userInputInteger < 4)
	{
		column = 0;
		row = userInputInteger - 1;
		ticTacToeTiles[column][row] = functionTurn;
	}
	else if ((3 < userInputInteger) && (userInputInteger < 7))
	{
		column = 1;
		row = userInputInteger - 4;
		ticTacToeTiles[column][row] = functionTurn;
	}
	else if ((6 < userInputInteger) && (userInputInteger < 10))
	{
		column = 2;
		row = userInputInteger - 7;
		ticTacToeTiles[column][row] = functionTurn;
	}

	screenWiper(30);
	for (int a{ 0 }; a < 3; a++)
	{
		std::cout << "\n";
		for (int b{ 0 }; b < 3; b++)
		{
			std::cout << ticTacToeTiles[a][b] << " ";
		}
	}
}
int aiRandom(char ticTacToeTiles[3][3]) //This function allows the "A.I." to randomly choose a non-chosen tile through brute force
{
	while (true)
	{
		std::mt19937 mt{ static_cast<std::mt19937::result_type>
			(std::chrono::high_resolution_clock::now().time_since_epoch().count()) };
		std::uniform_int_distribution<int> random{ 0, 2 };
		int column = random(mt);
		int row = random(mt);
		if (!(ticTacToeTiles[column][row] == 'X') && !(ticTacToeTiles[column][row] == 'O'))
		{
			return (3 * column) + (row + 1);
		}
	}

}
// missing function of restricting user input on occupied squares
bool drawChecker(char ticTacToeTiles[3][3]) //This function takes the board state and evaluates whether the final position is a draw
{
	int drawInt{ 0 };
	for (int column = 0; column < 3; column++)
	{
		for (int row = 0; row < 3; row++)
		{
			if ((ticTacToeTiles[column][row] == 'X') || (ticTacToeTiles[column][row] == 'O'))
			{
				drawInt++;
			}
		}
	}
	if (drawInt == 9)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}
int main()
{
	int userWinCount{ 0 };
	int aiWinCount{ 0 };
	rebootGame:
	{
		startUpTextFunction();
		char ticTacToeTiles[3][3] //This part generates the board, using array such that it doesn't trigger the win condition.
		{
			{'.',',','.'},
			{',','*',','},
			{'.',',','.'}
		};

		int userTurn{ turnRandomizer() };
		int aiTurn{};
		if (userTurn == 0)
		{
			aiTurn = 1;
		}
		else
		{
			aiTurn = 0;
		}
		int userInputInteger{};
		std::string continueString{};

		while (((ticTacToeTiles[0][0] == ticTacToeTiles[0][1]) && (ticTacToeTiles[0][0] == ticTacToeTiles[0][2])
			|| (ticTacToeTiles[1][0] == ticTacToeTiles[1][1]) && (ticTacToeTiles[1][0] == ticTacToeTiles[1][2])
			|| (ticTacToeTiles[2][0] == ticTacToeTiles[2][1]) && (ticTacToeTiles[2][0] == ticTacToeTiles[2][2])
			|| (ticTacToeTiles[0][0] == ticTacToeTiles[1][0]) && (ticTacToeTiles[0][0] == ticTacToeTiles[2][0])
			|| (ticTacToeTiles[0][1] == ticTacToeTiles[1][1]) && (ticTacToeTiles[0][1] == ticTacToeTiles[2][1])
			|| (ticTacToeTiles[0][2] == ticTacToeTiles[1][2]) && (ticTacToeTiles[0][2] == ticTacToeTiles[2][2])
			|| (ticTacToeTiles[0][0] == ticTacToeTiles[1][1]) && (ticTacToeTiles[0][0] == ticTacToeTiles[2][2])
			|| (ticTacToeTiles[0][2] == ticTacToeTiles[1][1]) && (ticTacToeTiles[0][2] == ticTacToeTiles[2][0]))
			== 0) //This mess checks for wins in the board using logical operators
		{
			if (userTurn == 0) //This section over here checks for the turns, so alternation is allowed
			{
				boardPrintout(10, ticTacToeTiles, userTurn);
				std::cout << "\nIt is currently your turn. Type 1-9 for your"
					" corresponding tile. \n-> ";
				std::cin >> userInputInteger;
				boardPrintout(userInputInteger, ticTacToeTiles, userTurn);
				userTurn++;
				if (drawChecker(ticTacToeTiles) == true)
				{
					userTurn = 2;
					break;
				}
			}
			else if (userTurn == 1)
			{
				boardPrintout(aiRandom(ticTacToeTiles), ticTacToeTiles, userTurn);
				std::cout << "\nThe A.I. has moved. Type anything to"
					" continue. \n-> ";
				std::cin >> continueString;
				boardPrintout(10, ticTacToeTiles, userTurn);
				userTurn--;
				if (drawChecker(ticTacToeTiles) == true)
				{
					userTurn = 2;
					break;
				}
			}



		}
		if (userTurn == 0)
		{
			++aiWinCount;
			std::cout << "\nYou have lost. The score is currently " << userWinCount << " - " << aiWinCount << ".";
		}
		else if (userTurn == 1)
		{
			++userWinCount;
			std::cout << "\nYou have won! The score is currently " << userWinCount << " - " << aiWinCount << ".";
		}
		else if (userTurn == 2)
		{
			std::cout << "\nThe game has been drawn. The score is still currently " << userWinCount << " - " << aiWinCount << ".";
		}
		std::cout << "\nPlay another? (YES or NO)\n-> ";
		std::cin >> continueString;
		if (continueString == "YES")
		{
			goto rebootGame;
		}
		else
		{
			std::cout << "Thank you for playing my game!";
			return 0;
		}
	}
} 
