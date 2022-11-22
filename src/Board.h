#pragma once

#include "Checker.h"
#include "Dice.h"
#include "Move.h"

enum Phase {BEAR_OFF = 0, STANDARD};

class Board
{
private:

	int blackPhase;
	int whitePhase;

	std::vector<std::string> table;

	int blackToBearOff;
	int whiteToBearOff;

	std::map<int, int> positions;

	std::vector<Checker*> checkersBlack;
	std::vector<Checker*> checkersWhite;

	std::map< int, std::vector<Checker*> > checkersOnPosition; // checkers on position(int) - vertically

	Move* lastMove;

	bool moveChecker; // when a player makes a move

	void initVariables();
	void initCheckersOnPosition();
	void initPositions();
	
public:
	Board(std::vector<Checker*> checkersBlack, std::vector<Checker*> checkersWhite);
	Board(const Board* board);

	virtual ~Board();

	void createTable();

	void makeMove(Move* move, Board* board);
	void makeSecondMove(Move* move, Board* board);

	bool isValidMove(Move* move, Dice* dice, int turn);

	void updateCheckersOnPosition();
	void updateUserMove(int color, Board* board);

	void updateCheckers(int color, Board* board);
	void printTable();

	bool getMoveChecker();
	Move* getLastMove();
	bool canCheckerMove(Checker* checker);
	bool canSecondCheckerMove(Checker* checker);
	std::vector<Board*> getChildren(int color, Dice* dice, Board* board);

	void updatePhase(int color);

	bool isValidMoveAI(int position, Checker* checker);

	bool isValidToPosition(int position, Checker* checker);

	std::vector<Checker*> getCheckers(int color);

	std::map< int, std::vector<Checker*> > getCheckersOnPosition();

	int searchForID(std::vector<Checker*> checkers, int id, int color); // returns 

	int getColorPhase(int color);

	/// <summary>
	/// checks if the state of the board comes to an end
	/// </summary>
	/// <returns>
	///  true if all the black checkers are collected in the position 0(by default)
	///  or if all the white checkers are collected in the position 25(by default)
	/// </returns>
	bool isTerminal();
};

