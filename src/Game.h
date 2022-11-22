#pragma once
#include "PlayerCPU.h"
#include "Board.h"
#include "Move.h"

class Game
{
private:

	//Players
	PlayerCPU* cpuWhite;
	PlayerCPU* cpuBlack;
	
	//Board
	Board* board;

	//Dice
	Dice* dice;

	//Move
	Move* move;
	bool secondMove; // played one dice

	bool wrongInput;

	int currentTurn;

	bool gameTerminated;

	void initPlayer();
	void initBoard();
	void initDice();

public:
	Game();
	virtual ~Game();
	void GameLoop();

	void setCurrentTurn(int currentTurn);
	int getCurrentTurn();

	void bearOff();
};


/*
*	TO DO:
	- Double move not implemented yet -> problem when the dice indexes are the same
	- isTerminal() 
*/

