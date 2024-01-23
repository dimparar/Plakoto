#pragma once

enum CheckerColor { WHITE = 0, BLACK };

class Checker
{
private:
	int position;
	int color;

	int id;

public:
	Checker(int color, int id);
	Checker(const Checker* checker);
	virtual ~Checker();

	std::string render();

	void setPosition(int position);
	int getPosition();

	int getColor();
	int getId();
};

