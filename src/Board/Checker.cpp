#include "stdafx.h"
#include "Checker.h"

Checker::Checker(int color, int id)
{
	this->color = color;
	this->id = id;
}

Checker::Checker(const Checker* checker)
{
	this->color = checker->color;
	this->position = checker->position;
	this->id = checker->id;
}

Checker::~Checker()
{
}

std::string Checker::render()
{
	if (this->color == WHITE)
	{
		return "w";
	}
	else
	{
		return "b";
	}
	
}

void Checker::setPosition(int position)
{
	this->position = position;
}

int Checker::getPosition()
{
	return this->position;
}

int Checker::getColor()
{
	return color;
}

int Checker::getId()
{
	return this->id;
}
