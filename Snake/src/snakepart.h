#pragma once

#include "defines.h"
#include <QPainter>

class Snake;

class SnakePart 
{
	friend Snake;
public:
	SnakePart();
	SnakePart(Pos, int direction);
	SnakePart(int x, int y, int direction);
	~SnakePart();

	void paint(QPainter& painter) const;
	void move();
	void changeDir(int dir);

	int getDir() const	{ return _direction; }
	Pos getPos() const	{ return _position;  }

private:
	int _size;
	Pos _position;
	int _direction;
};
