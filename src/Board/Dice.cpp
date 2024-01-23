#include "stdafx.h"
#include "Dice.h"

Dice::Dice()
{
	this->dice1 = 0;
	this->dice2 = 0;

	this->playedDice1 = false;
	this->playedDice2 = false;
}

Dice::Dice(int dice_1, int dice_2, float odds)
	: dice1(dice_1), dice2(dice_2), odds(odds)
{

}

Dice::~Dice()
{
}

void Dice::rollTheDice()
{
	this->dice1 = rand() % 6 + 1;
	this->dice2 = rand() % 6 + 1;
}

std::vector<Dice*> Dice::getChildren()
{
	std::vector<Dice*> children;

	for (int dice_1 = 1; dice_1 <= 6; dice_1++)
	{
		for (int dice_2 = dice_1; dice_2 <= 6; dice_2++)
		{
			if (dice_1 == dice_2)
			{
				children.push_back(new Dice(dice_1, dice_2, this->oddsSameDice));
			}
			else
			{
				children.push_back(new Dice(dice_1, dice_2, this->oddsDifferentDice));
			}
		}
	}

	return children;
}

int Dice::getDice1()
{
	return this->dice1;
}

int Dice::getDice2()
{
	return this->dice2;
}

bool Dice::getPlayedDice1()
{
	return this->playedDice1;
}

bool Dice::getPlayedDice2()
{
	return this->playedDice2;
}

void Dice::setPlayedDice1(bool played_dice_1)
{
	this->playedDice1 = played_dice_1;
}

void Dice::setPlayedDice2(bool played_dice_2)
{
	this->playedDice2 = played_dice_2;

}

float Dice::getOdds()
{
	return this->odds;
}
