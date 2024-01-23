#pragma once
class Move
{
private:
	int fromPosition;
	int toPosition;
	int fromPosition_1;//if the player make two moves
	int toPosition_1;//if the player make two moves

	int value;
	

public:
	Move(int from_position, int to_position);
	Move(int from_position, int to_position, int value);
	Move(int value);
	virtual ~Move();

	int getFromPosition();
	int getToPosition();

	void setFromPosition(int from_position);
	void setToPosition(int to_position);

	void setFromPosition_1(int from_position_1);
	void setToPosition_1(int to_position_1);

	int getFromPosition_1();
	int getToPosition_1();

	int getValue();
	void setValue(int value);

};

