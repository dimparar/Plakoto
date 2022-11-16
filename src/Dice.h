#pragma once

class Dice
{
private:
	int dice1;
	int dice2;
	
	bool playedDice1;
	bool playedDice2;

	const float oddsSameDice = 0.27;
	const float oddsDifferentDice = 0.05;

	float odds;

public:
	Dice();
	Dice(int dice_1, int dice_2, float odds);
	virtual ~Dice();

	void rollTheDice();

	std::vector<Dice*> getChildren();

	int getDice1();
	int getDice2();

	bool getPlayedDice1();
	bool getPlayedDice2();

	void setPlayedDice1(bool played_dice_1);
	void setPlayedDice2(bool played_dice_2);

	float getOdds();

};

