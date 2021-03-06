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
	SnakePart(QPoint, int direction);
	SnakePart(int x, int y, int direction);
	~SnakePart();

	void paint(QPainter& painter, int r, int g, int b) const override;
	void move();

	void setDir(int dir) { _direction = dir; }

	int getDir() const	{ return _direction; }

private:
	int _direction;
};
