#include "snakepart.h"


SnakePart::SnakePart()
{
	_size = BLOCK_SIZE;
	_position = Pos();
	_direction = right;
}

SnakePart::SnakePart(Pos pos, int direction) : _size(BLOCK_SIZE), _position(pos), _direction(direction)
{
	
}

SnakePart::SnakePart(int x, int y, int direction) : _size(BLOCK_SIZE), _position(Pos(x, y)), _direction(direction)
{
	
}

SnakePart::~SnakePart()
{
	
}

void SnakePart::paint(QPainter& painter) const
{
	painter.setBrush(QColor("#88BB77"));
	painter.drawRect(_position.x * BLOCK_SIZE, _position.y * BLOCK_SIZE, _size, _size);
}

void SnakePart::move()
{
	if (_direction == left)
		_position.x -= 1;
	else if (_direction == right)
		_position.x += 1;
	else if (_direction == up)
		_position.y -= 1;
	else if (_direction == down)
		_position.y += 1;
}

void SnakePart::changeDir(int dir)
{
	_direction = dir;
}