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
	//myFile_Handler.open("C:/Users/trian/OneDrive/Υπολογιστής/Plakoto_Project/File_1.txt");
}

PlayerCPU::~PlayerCPU()
{
	//myFile_Handler.close();
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

/// <summary>
/// Max creates for the dice the possible move-children and for every child it calls the chance 
/// the children of the max node are chance nodes
/// </summary>
/// <param name="board"></param>
/// <param name="dice"></param>
/// <param name="depth"></param>
/// <returns>move with value max(for every chance-child take the chance.node.value)</returns>
Move* PlayerCPU::Max(Board* board, Dice* dice, int depth)
{

	//check depth or ending state
	this->currentNode = MAX;

	//the bot gives his checkers in order to find the possible state children
	std::vector<Board*> children = board->getChildren(BLACK, dice, board);
	Move* maxMove;
	maxMove = new Move(INT_MIN);
	
	//std::vector<std::string> practice;
	for (auto child : children)
	{
		//std::cout << "here" << "\n";
		Move* move;
		move = this->chance(child, dice, depth + 1);
		
		/*std::string s = std::to_string(dice->getDice1()) + " " + std::to_string(dice->getDice2()) + ' ' + std::to_string(depth) + " " + " Max for loop children" + " from_position: " + std::to_string(move->getFromPosition()) + " Toposition: " + std::to_string(move->getToPosition());
		
		if (move->getFromPosition() != -1)
		{
			s +=  "  from position 1 : " + std::to_string(move->getFromPosition_1()) + "  from position 1 : " + std::to_string(move->getToPosition_1()) + "\n";
		}*/
		//practice.push_back(s);
		//std::cout << " Possible Move " << move->getFromPosition() << " to " << move->getToPosition() << "\n";
		//std::cout << " Possible Move " << move->getFromPosition_1() << " to " << move->getToPosition_1() << "\n";
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
	/*for (auto i : practice)
	{
		myFile_Handler << i;
	}
	myFile_Handler << "\n\n\n\n";*/
	/*std::cout << "MaxMove:" << maxMove->getFromPosition() << " to " << maxMove->getToPosition() << "\n";
	std::cout << "MaxMove_1:" << maxMove->getFromPosition_1() << " to " << maxMove->getToPosition_1() << "\n";
	std::cout << "---------------------------------------------------------------" << "\n";*/

	return maxMove;
}

/// <summary>
/// Min creates for the dice the possible move-children and for every child it calls the chance 
/// the children of the min node are chance nodes
/// </summary>
/// <param name="board"></param>
/// <param name="dice"></param>
/// <param name="depth"></param>
/// <returns>move with value min(for every chance-child take the chance.node.value)</returns>
Move* PlayerCPU::Min(Board* board, Dice* dice, int depth)
{

	//check depth or ending state
	this->currentNode = MIN;

	//the bot gives his checkers in order to find the possible state children
	std::vector<Board*> children = board->getChildren(WHITE, dice, board);
	Move* minMove;
	minMove = new Move(INT_MAX);

	//std::vector<std::string> practice;
	for (auto child : children)
	{
		Move* move;
		move = this->chance(child, dice, depth + 1);
		
		/*std::string s = std::to_string(dice->getDice1()) + " " + std::to_string(dice->getDice2()) + ' ' + std::to_string(depth) + " " + " Min for loop children" + " from_position: " + std::to_string(move->getFromPosition()) + " Toposition: " + std::to_string(move->getToPosition());

		if (move->getFromPosition() != -1)
		{
			s += "  from position 1 : " + std::to_string(move->getFromPosition_1()) + "  from position 1 : " + std::to_string(move->getToPosition_1()) + "\n";
		}
		practice.push_back(s);*/
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
	/*for (auto i : practice)
	{
		myFile_Handler << i;
	}
	myFile_Handler << "\n\n\n\n";*/

	/*std::cout << "MinMove:" << minMove->getFromPosition() << " to " << minMove->getToPosition() << "\n";
	std::cout << "MinMove_1:" << minMove->getFromPosition_1() << " to " << minMove->getToPosition_1() << "\n";
	std::cout << "---------------------------------------------------------------" << "\n";*/

	return minMove;
}

/// <summary>
/// Creates all the possible dice and for every child calls min or max
/// </summary>
/// <param name="board"></param>
/// <param name="dice"></param>
/// <param name="depth"></param>
/// <returns> the move with value: (sum += possibility*(move->value))</returns>
Move* PlayerCPU::chance(Board* board, Dice* dice, int depth)
{

	if (board->isTerminal() || depth == this->maxDepth)
	{
		// TO DO
		Move* move;
		move = new Move(board->getLastMove()->getFromPosition(), board->getLastMove()->getToPosition(), 2); // evaluate
		move->setFromPosition_1(board->getLastMove()->getFromPosition_1());
		move->setToPosition_1(board->getLastMove()->getToPosition_1());
		
		return move;
	}

	std::vector<Dice*> children = dice->getChildren();

	float sum = 0.0;
	int test = 0;
	std::vector<Move*> Moves;
	for (auto child : children)
	{
		Move* move;
		if (this->currentNode == MIN)
		{
			//std::cout << "dice: " << test << "\n";
			test++;
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

	/*std::cout << "ChanceMove:" << chanceMove->getFromPosition() << " to " << chanceMove->getToPosition() << "\n";
	std::cout << "ChanceMove_1:" << chanceMove->getFromPosition_1() << " to " << chanceMove->getToPosition_1() << "\n";
	std::cout << "---------------------------------------------------------------" << "\n";*/

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
