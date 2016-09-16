#pragma once

#include "defines.h"
#include <QPainter>


class Block
{
public:
	Block();
#if 0
	Block(Pos pos);
	Block(int x, int y);
#endif
	virtual ~Block();

	Pos getPos() const	{ return _position; }
	virtual void paint(QPainter& painter) const = 0;

protected:
	int _size;
	Pos _position;
};
