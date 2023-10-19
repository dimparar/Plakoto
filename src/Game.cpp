#include "stdafx.h"
#include "Game.h"

//Private
void Game::initPlayer()
{
	this->cpuWhite = new PlayerCPU(WHITE, 1);
	this->cpuBlack = new PlayerCPU(BLACK, 1);
	
	for (auto i : this->cpuBlack->getCheckers())
	{
		i->setPosition(1);
	}

	for (auto i : this->cpuWhite->getCheckers())
	{
		i->setPosition(24);
	}
}

void Game::initBoard()
{
	this->board = new Board(cpuBlack->getCheckers(), cpuWhite->getCheckers());
}

void Game::initDice()
{
	this->dice = new Dice();
}

//Public
Game::Game()
{
	this->coloredTable = false;
	this->currentTurn = BLACK;
	this->gameTerminated = false;
	this->move = nullptr;
	this->wrongInput = false;

	this->initDice();
	this->initPlayer();
	this->initBoard();

}

Game::~Game()
{
	delete this->dice;

	delete this->board;
}

void Game::GameLoop()
{
	std::cout << "White Depth: " << this->cpuWhite->getDepth() << "\n";
	std::cout << "Black Depth: " << this->cpuBlack->getDepth() << "\n";

	int counter_no_play = 0;
	this->board->createTable();

	this->dice->rollTheDice(); // roll the dice

	this->board->updateCheckers(BLACK, this->board);
	this->board->updateCheckers(WHITE, this->board);

	this->board->printTable();
	
	system("pause");
	std::system("cls");

	//Game Loop
	while (!this->board->isTerminal())
	{	
		std::cout << "Dice 1: " << this->dice->getDice1() << "\n";
		std::cout << "Dice 2: " << this->dice->getDice2() << "\n";

		std::string playername;
		if (this->getCurrentTurn() == WHITE)
		{
			playername = "White ";
		}
		else
		{
			playername = "Black ";
		}

		std::cout << playername << "plays now" << std::endl;
		if (this->getCurrentTurn() == WHITE)
		{
			Move* move = this->cpuWhite->MiniMax(this->board, this->dice);
			
			if (move->getFromPosition() != -1)
			{
				this->board->makeMove(move, this->board);
				std::cout << "Chosen Move " << move->getFromPosition() << " to " << move->getToPosition() << "\n";
				std::cout << "Chosen Move " << move->getFromPosition_1() << " to " << move->getToPosition_1() << "\n";
				this->board->updatePhase(WHITE);

				if (move->getFromPosition_1() != -1)
				{
					this->board->makeSecondMove(move, this->board);
				}

				this->board->updateCheckers(WHITE, this->board);
			}
			else
			{
				std::cout << "No move to play!" << "\n";
			}

			this->dice->rollTheDice();

			this->setCurrentTurn(BLACK);

			// end of round
		}
		else
		{
			Move* move = this->cpuBlack->MiniMax(this->board, this->dice);

			if (move->getFromPosition() != -1)
			{
				counter_no_play = 0;
				this->board->makeMove(move, this->board);
				std::cout << "Chosen Move " << move->getFromPosition() << " to " << move->getToPosition() << "\n";
				std::cout << "Chosen Move " << move->getFromPosition_1() << " to " << move->getToPosition_1() << "\n";
				this->board->updatePhase(BLACK);

				if (move->getFromPosition_1() != -1)
				{
					this->board->makeSecondMove(move, this->board);
				}

				this->board->updateCheckers(BLACK, this->board);
			}
			else
			{
				std::cout << "No move to play!" << "\n";
			}

			this->setCurrentTurn(WHITE);

			this->dice->rollTheDice();

		}

		this->board->printTable();
		std::system("pause");
		std::system("cls");
	}

	int sum_black = 0;
	std::cout << "Game Over" << "\n";
	for (auto bl : board->getCheckers(BLACK))
	{
		if (bl->getPosition() == 25)
			sum_black++;
	}

	int sum_white = 0;
	for (auto wh : board->getCheckers(WHITE))
	{
		if (wh->getPosition() == 0)
			sum_white++;
	}

	if (this->board->getTie())
	{
		std::cout <<  "It's a tie\n";
	}
	else if (sum_black > sum_white)
	{
		std::cout << "Winner is: Black\n";
	}
	else
	{
		std::cout << "Winner is: White\n" ;
	}

	//system("pause");
}

void Game::setCurrentTurn(int currentTurn)
{
	this->currentTurn = currentTurn;
}

int Game::getCurrentTurn()
{
	return this->currentTurn;
}

void Game::setBlackDepth(int max_depth)
{
	this->cpuBlack->setDepth(max_depth);
}

void Game::setWhiteDepth(int max_depth)
{
	this->cpuWhite->setDepth(max_depth);
}

