#include "stdafx.h"
#include "Move.h"

Move::Move(int from_position, int to_position)
{
	this->fromPosition = from_position;
	this->toPosition = to_position;
	this->fromPosition_1 = -1;
	this->toPosition_1 = -1;
}

Move::Move(int from_position, int to_position, int value)
{
	this->fromPosition = from_position;
	this->toPosition = to_position;
	this->fromPosition_1 = -1;
	this->toPosition_1 = -1;
	this->value = value;
}

Move::Move(int value)
{
	this->value = value;
	this->fromPosition = -1;
	this->toPosition = -1;
	this->fromPosition_1 = -1;
	this->toPosition_1 = -1;
}

Move::~Move()
{
}

int Move::getFromPosition()
{
	return this->fromPosition;
}

int Move::getToPosition()
{
	return this->toPosition;
}

void Move::setFromPosition(int from_position)
{
	this->fromPosition = from_position;
}

void Move::setToPosition(int to_position)
{
	this->toPosition = to_position;
}

void Move::setFromPosition_1(int from_position_1)
{
	this->fromPosition_1 = from_position_1;
}

void Move::setToPosition_1(int to_position_1)
{
	this->toPosition_1 = to_position_1;
}

int Move::getFromPosition_1()
{
	return this->fromPosition_1;
}

int Move::getToPosition_1()
{
	return this->toPosition_1;
}

int Move::getValue()
{
	return this->value;
}

void Move::setValue(int value)
{
	this->value = value;
}
