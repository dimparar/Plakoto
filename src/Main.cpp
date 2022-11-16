#include "stdafx.h"
#include "Game.h"

int main(int argc, char** argv)
{
	std::srand(static_cast<unsigned>(time(NULL)));

	Game game = Game();

	//char a = L"\u0444";
	//std::cout << L"\u231C" << "\n";

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	printf("red text\n");

	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	printf("green text\n");
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	

	game.GameLoop();
}