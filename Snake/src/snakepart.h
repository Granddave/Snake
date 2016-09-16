#pragma once

#include "defines.h"
#include "block.h"

// Forward declaration
class Snake;

class SnakePart : public Block
{
	friend Snake;
public:
	SnakePart();
	SnakePart(Pos, int direction);
	SnakePart(int x, int y, int direction);
	~SnakePart();

	void paint(QPainter& painter) const override;
	void move();

	void setDir(int dir) { _direction = dir; }

	int getDir() const	{ return _direction; }

private:
	int _direction;
};
