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
	
	this->board->createTable();
	//this->board->updateCheckersOnPosition();

	this->dice->rollTheDice(); // roll the dice

	this->board->updateCheckers(BLACK, this->board);
	this->board->updateCheckers(WHITE, this->board);

	this->board->printTable();

	//Game Loop
	while (!this->board->isTerminal())
	{	
		//system("cls"); // clear terminal

		std::cout << "Dice 1: " << this->dice->getDice1() << "\n";
		std::cout << "Dice 2: " << this->dice->getDice2() << "\n";

		/// <summary>
		/// To parakatw 8a alax8ei gia thn emfanish tou player
		/// </summary>
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
				//this->board->printTable();
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
				this->board->makeMove(move, this->board);
				std::cout << "Chosen Move " << move->getFromPosition() << " to " << move->getToPosition() << "\n";
				std::cout << "Chosen Move " << move->getFromPosition_1() << " to " << move->getToPosition_1() << "\n";

				this->board->updatePhase(BLACK);

				if (move->getFromPosition_1() != -1)
				{
					this->board->makeSecondMove(move, this->board);
				}

				this->board->updateCheckers(BLACK, this->board);
				//this->board->printTable();
			}
			else
			{
				std::cout << "No move to play!" << "\n";
			}

			this->setCurrentTurn(WHITE);

			this->dice->rollTheDice();

		}

		this->board->printTable();

		/*std::cout << "BLACK Checkers" << "\n";
		for (auto i : this->board->getCheckers(BLACK))
		{
			std::cout << "Id: " << i->getId() << " Position: " << i->getPosition() << "\n";
		}

		std::cout << "WHITE Checkers" << "\n";
		for (auto i : this->board->getCheckers(WHITE))
		{
			std::cout << "Id: " << i->getId() << " Position: " << i->getPosition() << "\n";
		}
		std::cout << "---------------------------------------------------------------------" << "\n";

		std::cout << "CheckersOnPosition" << "\n";
		for (auto i : this->board->getCheckersOnPosition())
		{
			for (auto j : i.second)
			{
				std::cout << "Id: " << j->getId() << " Position: " << j->getPosition() << "\n";
			}
		}*/
		//system("pause");
	}

	std::cout << "Game Over" << "\n";

}

void Game::setCurrentTurn(int currentTurn)
{
	this->currentTurn = currentTurn;
}

int Game::getCurrentTurn()
{
	return this->currentTurn;
}

void Game::bearOff()
{



}
