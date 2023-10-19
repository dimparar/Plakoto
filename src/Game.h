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
	bool coloredTable;

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

	void setBlackDepth(int max_depth);
	void setWhiteDepth(int max_depth);

};


