#pragma once

#include "defines.h"

class Block
{
public:
	Block();
#if 0
	Block(Pos pos);
	Block(int x, int y);
#endif
	virtual ~Block();

	virtual void paint(QPainter& painter, int r, int g, int b) const;
	virtual void paint(QPainter& painter) const;

	Pos getPos() const	{ return _position; }

protected:
	int _size = BLOCK_SIZE;
	Pos _position;
};
