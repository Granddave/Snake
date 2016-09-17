#pragma once

#include "defines.h"
#include "QPoint"

class Block
{
public:
	Block();
	Block(QPoint pos);
#if 0
	Block(int x, int y);
#endif
	virtual ~Block();

	virtual void paint(QPainter& painter, int r, int g, int b) const;
	virtual void paint(QPainter& painter) const;

	QPoint getPos() const { return _position; }

protected:
	int _size = BLOCK_SIZE;
	QPoint _position;
};
