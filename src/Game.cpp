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
	this->secondMove = false;

	this->initDice();
	this->initPlayer();
	this->initBoard();

}

Game::~Game()
{
	delete this->cpuWhite;
	delete this->cpuBlack;

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
	while (!this->gameTerminated)
	{	
		
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
			//play round
			//this->cpuWhite->minimax();//Board!
			
			//std::string player_move;

			//while (!this->wrongInput && !this->move || this->wrongInput)
			//{
			//	//std::cout << "Move -> ex. move from 1 to 5 -> 1-5" << "\n";
			//	std::cout << "Your Move: ";
			//	std::getline(std::cin, player_move);
			//	
			//	this->move = this->parseInput(player_move, this->getCurrentTurn());

			//}

			//if (this->dice->getPlayedDice1() && this->dice->getPlayedDice2())
			//{
			//	this->setCurrentTurn(BLACK);
			//	this->dice->rollTheDice();
			//	this->dice->setPlayedDice1(false);
			//	this->dice->setPlayedDice2(false);
			//	
			//}
			//else
			//{
			//	this->secondMove = true;
			//}
			//this->board->makeMove(this->move, this->board);
			//this->move = nullptr;

			Move* move = this->cpuWhite->MiniMax(this->board, this->dice);
			
			if (move->getFromPosition() != -1)
			{
				this->board->makeMove(move, this->board);
				std::cout << "Chosen Move " << move->getFromPosition() << " to " << move->getToPosition() << "\n";
				std::cout << "Chosen Move " << move->getFromPosition_1() << " to " << move->getToPosition_1() << "\n";

				this->board->updateCheckers(WHITE, this->board);
				this->board->printTable();
			}
			else
			{
				std::cout << "No move to play!" << "\n";
			}


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

				this->board->updateCheckers(BLACK, this->board);
				this->board->printTable();
			}
			else
			{
				std::cout << "No move to play!" << "\n";
			}

			//std::string player_move;

			//while (!this->wrongInput && !this->move || this->wrongInput)
			//{
			//	//std::cout << "Move -> ex. move from 1 to 5 -> 1-5" << "\n";
			//	std::cout << "Your Move: ";
			//	std::getline(std::cin, player_move);

			//	this->move = this->parseInput(player_move, this->getCurrentTurn());
			//}

			//// if black has played both moves then white plays next
			//if (this->dice->getPlayedDice1() && this->dice->getPlayedDice2())
			//{
			//	this->setCurrentTurn(WHITE);
			//	this->dice->rollTheDice();
			//	this->dice->setPlayedDice1(false);
			//	this->dice->setPlayedDice2(false);
			//	this->secondMove = false;
			//}
			//else
			//{
			//	this->secondMove = true;
			//}

			//this->board->makeMove(this->move, this->board);
			
			this->setCurrentTurn(WHITE);
			this->move = nullptr;
		}

		this->dice->rollTheDice(); // roll the dice

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

		//system("cls"); // clear terminal
	}

}

Move* Game::parseInput(std::string input, int turn)
{
	int i = 0;
	std::string from_position;
	std::string to_position;
	this->wrongInput = false;

	while (!this->wrongInput)
	{
		if (input[i] == '-')
		{
			break;
		}

		from_position += input[i];
		i++;

		if (i > input.length())
		{
			this->wrongInput = true;
		}
	}

	if (!this->wrongInput)
	{
		i++;
		while (input[i])
		{
			to_position += input[i];
			i++;
		}
	}

	// check input

	for (auto i : from_position)
	{
		if (!std::isdigit(i))
		{
			this->wrongInput = true;
			break;
		}
	}

	if (!this->wrongInput)
	{
		for (auto i : to_position)
		{
			if (!std::isdigit(i))
			{
				this->wrongInput = true;
				break;
			}
		}
	}

	if (!this->wrongInput)
	{
		if (!(std::stoi(from_position) >= 1 && std::stoi(from_position) <= 24 && std::stoi(to_position) >= 1 && std::stoi(to_position) <= 24))
		{
			this->wrongInput = true;
		}
		if (turn == WHITE)// from the top to the bottom check that the WHITE doesn't go backwards
		{
			if (!(std::stoi(to_position) - std::stoi(from_position) < 0))
			{
				this->wrongInput = true;
			}

		}
		else if (turn == BLACK)// from the bottom to the top check that the BLACK doesn't go backwards
		{
			if (!(std::stoi(to_position) - std::stoi(from_position) > 0))
			{
				this->wrongInput = true;
			}
		}
	}

	if (this->wrongInput)
	{
		std::cout << "Not a valid move::error_1" << std::endl << std::endl;
		return nullptr;
	}
	else
	{
		Move* move;
		if (!this->secondMove) // true: played only one dice or both
		{
			move = new Move(std::stoi(from_position), std::stoi(to_position));
		}
		else
		{
			move = new Move(std::stoi(from_position), std::stoi(to_position));
			move->setFromPosition_1(this->board->getLastMove()->getFromPosition());
			move->setToPosition_1(this->board->getLastMove()->getToPosition());
		}

		if (board->isValidMove(move, dice, turn))
		{
			this->wrongInput = false;
			return move;
		}
		else
		{
			std::cout << "Not a valid move::error_2" << std::endl << std::endl;
			return nullptr;
		}
	}
	
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
	//for (auto i : this->)


}
