#include "block.h"

Block::Block()
{
}

Block::Block(Pos pos) : _size(BLOCK_SIZE), _position(pos)
{
}
#if 0

Block::Block(int x, int y) : _size(BLOCK_SIZE), _position(Pos(x, y))
{
}
#endif


Block::~Block()
{
}

void Block::paint(QPainter& painter, int r, int g, int b) const
{
}

void Block::paint(QPainter& painter) const
{
}
