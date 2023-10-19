#include "stdafx.h"
#include "Game.h"

int main(int argc, char** argv)
{
	std::srand(static_cast<unsigned>(time(NULL)));

	Game game = Game();

	std::string answer;
	std::cout << "Enter (yes or no): ";
	std::getline(std::cin, answer);

	std::string answer_1;
	std::cout << "Depth for White: ";
	std::getline(std::cin, answer_1);
	game.setWhiteDepth(std::stoi(answer_1));

	std::string answer_2;
	std::cout << "Depth for Black: ";
	std::getline(std::cin, answer_2);
	game.setBlackDepth(std::stoi(answer_2));

	if (answer == "yes")
	{
		system("cls");

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

		std::string message = "I see,";
		std::string message_1 = " so you have the guts to challenge me \n";
		std::string message_2 = "Let the game begin";
		std::string message_3 = "PLAKOTO";
		for (auto i : message)
		{
			std::cout << i;
			std::system("timeout 0 > nul");
		}
		std::system("timeout 2 > nul");

		for (auto i : message_1)
		{
			std::cout << i;
			std::system("timeout 0 > nul");
		}
		std::system("timeout 2 > nul");

		for (auto i : message_2)
		{
			std::cout << i;
			std::system("timeout 0 > nul");
		}
		
		std::system("timeout 1 > nul");

		std::system("cls");

		for (auto i : message_3)
		{
			std::cout << i;
			std::system("timeout 0 > nul");
		}

		std::system("timeout 2 > nul");

		std::cout << "\n";

		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	}

	game.GameLoop();
}