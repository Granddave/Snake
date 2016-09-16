#pragma once

#include "defines.h"
#include "block.h"
#include <QtGui/QPainter>

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
	void changeDir(int dir) { _direction = dir;	}


	int getDir() const	{ return _direction; }

private:
	int _direction;
};
