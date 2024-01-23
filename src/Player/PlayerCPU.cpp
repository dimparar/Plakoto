#include "stdafx.h"
#include "PlayerCPU.h"

void PlayerCPU::initCheckers(int color)
{
	// initialize 15 checkers
	int i = 0;
	while (i < 15)
	{
		this->checkers.push_back(new Checker(color, i));
		i++;
	}
	this->color = color;

}

PlayerCPU::PlayerCPU(int color, int max_depth)
{
	this->initCheckers(color);
	this->maxDepth = max_depth;
}

PlayerCPU::~PlayerCPU()
{
	for (auto i : this->checkers)
	{
		delete i;
	}
}

Move* PlayerCPU::MiniMax(Board* board, Dice* dice)
{
	if (this->color == BLACK)
	{
		return this->Max(new Board(board), dice, 0);
	}
	else
	{
		return this->Min(new Board(board), dice, 0);
	}
}


// Max creates for the dice the possible move-children and for every child it calls the chance 
// the children of the max node are chance nodes
// returns a move with value max(for every chance-child take the chance.node.value)
Move* PlayerCPU::Max(Board* board, Dice* dice, int depth)
{

	//check depth or ending state
	this->currentNode = MAX;

	//the bot gives his checkers in order to find the possible state children
	std::vector<Board*> children = board->getChildren(BLACK, dice, board);
	Move* maxMove;
	maxMove = new Move(INT_MIN);
	
	for (auto child : children)
	{
		Move* move;
		move = this->chance(child, dice, depth + 1);
				
		if (move->getValue() >= maxMove->getValue())
		{
			if (move->getValue() == maxMove->getValue())
			{
				if (std::rand() % 2 == 0)
				{
					maxMove->setFromPosition(child->getLastMove()->getFromPosition());
					maxMove->setToPosition(child->getLastMove()->getToPosition());				
					maxMove->setFromPosition_1(child->getLastMove()->getFromPosition_1());
					maxMove->setToPosition_1(child->getLastMove()->getToPosition_1());
					maxMove->setValue(move->getValue());
				}
			}
			else
			{
				maxMove->setFromPosition(child->getLastMove()->getFromPosition());
				maxMove->setToPosition(child->getLastMove()->getToPosition());				
				maxMove->setFromPosition_1(child->getLastMove()->getFromPosition_1());
				maxMove->setToPosition_1(child->getLastMove()->getToPosition_1());
				maxMove->setValue(move->getValue());
			}
		}
	}

	return maxMove;
}


// Min creates for the dice the possible move-children and for every child it calls the chance 
// the children of the min node are chance nodes
// returns a move with value min(for every chance-child take the chance.node.value)
Move* PlayerCPU::Min(Board* board, Dice* dice, int depth)
{

	//check depth or ending state
	this->currentNode = MIN;

	//the bot gives his checkers in order to find the possible state children
	std::vector<Board*> children = board->getChildren(WHITE, dice, board);
	Move* minMove;
	minMove = new Move(INT_MAX);

	for (auto child : children)
	{
		Move* move;
		move = this->chance(child, dice, depth + 1);
		
		if (move->getValue() <= minMove->getValue())
		{
			if (move->getValue() == minMove->getValue())
			{
				if (std::rand() % 2 == 0)
				{
					minMove->setFromPosition(child->getLastMove()->getFromPosition());
					minMove->setToPosition(child->getLastMove()->getToPosition());
					minMove->setFromPosition_1(child->getLastMove()->getFromPosition_1());
					minMove->setToPosition_1(child->getLastMove()->getToPosition_1());
					minMove->setValue(move->getValue());
				}
			}
			else
			{
				minMove->setFromPosition(child->getLastMove()->getFromPosition());
				minMove->setToPosition(child->getLastMove()->getToPosition());
				minMove->setFromPosition_1(child->getLastMove()->getFromPosition_1());
				minMove->setToPosition_1(child->getLastMove()->getToPosition_1());

				minMove->setValue(move->getValue());
			}
		}
	}

	return minMove;
}

// Creates all the possible dice and for every child calls min or max
// returns the move with 
//returns (sum += possibility*(move->value))
Move* PlayerCPU::chance(Board* board, Dice* dice, int depth)
{

	if (board->isTerminal() || depth == this->maxDepth)
	{
		Move* move;
		move = new Move(board->getLastMove()->getFromPosition(), board->getLastMove()->getToPosition(), board->evaluate());
		move->setFromPosition_1(board->getLastMove()->getFromPosition_1());
		move->setToPosition_1(board->getLastMove()->getToPosition_1());
		
		return move;
	}

	std::vector<Dice*> children = dice->getChildren();

	float sum = 0.0;
	std::vector<Move*> Moves;
	for (auto child : children)
	{
		Move* move;
		if (this->currentNode == MIN)
		{
			move = Max(board, child, depth + 1);
			this->currentNode = MIN;
		}
		else
		{
			move = Min(board, child, depth + 1);
			this->currentNode = MAX;
		}

		Moves.push_back(move);
		sum += move->getValue() * child->getOdds();
	}

	float min_move = INT_MAX;
	Move* chanceMove;
	chanceMove = nullptr; // smallest distance from sum

	for (auto i : Moves)
	{
		if (min_move >= std::abs(sum - i->getValue()))
		{
			if (min_move == std::abs(sum - i->getValue()))
			{
				if (rand() % 2 == 0)
				{
					min_move = std::abs(sum - i->getValue());
					chanceMove = i;
				}
			}
			else
			{
				min_move = std::abs(sum - i->getValue());
				chanceMove = i;
			}
		}
	}

	return chanceMove;
}

std::vector<Checker*> PlayerCPU::getCheckers()
{
	return this->checkers;
}

void PlayerCPU::setCheckersPosition(int checker, int newPos)
{
	this->checkers[checker]->setPosition(newPos);
}

void PlayerCPU::setDepth(int max_depth)
{
	this->maxDepth = max_depth;
}

int PlayerCPU::getDepth()
{
	return this->maxDepth;
}
