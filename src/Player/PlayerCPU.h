#pragma once
#include "Board.h";

enum CurrentNode {MAX = 0, MIN};

class PlayerCPU
{
private:
	std::vector<Checker*> checkers;
	int color;

	int currentNode;

	int maxDepth;

	void initCheckers(int color);

public:
	PlayerCPU(int color, int max_depth);
	virtual ~PlayerCPU();

	Move* MiniMax(Board* board, Dice* dice);

	Move* Min(Board* Board, Dice* dice, int depth = 0);
	Move* Max(Board* Board, Dice* dice, int depth = 0);

	Move* chance(Board* board, Dice* dice, int depth);

	std::vector<Checker*> getCheckers();

	void setCheckersPosition(int checker, int newPos);

	void setDepth(int max_depth);
	int getDepth();
};

