#include "snakepart.h"


SnakePart::SnakePart()
{
	_size = BLOCK_SIZE;
	_position = QPoint();
	_direction = _right;
}

SnakePart::SnakePart(QPoint pos, int direction)
{
	_size = BLOCK_SIZE;
	_position = pos;
	_direction = direction;
}

SnakePart::SnakePart(int x, int y, int direction)
{
	_size = BLOCK_SIZE;
	_position = QPoint(x, y);
	_direction = direction;
}

SnakePart::~SnakePart()
{
}

void SnakePart::paint(QPainter& painter, int r, int g, int b) const
{
	painter.setBrush(QColor(r, g, b, 255)); //"#88BB77"
	painter.drawRect(_position.x() * BLOCK_SIZE, _position.y() * BLOCK_SIZE, _size, _size);
}

void SnakePart::move()
{
	if (_direction == _left)
		_position.rx()--;
	else if (_direction == _right)
		_position.rx()++;
	else if (_direction == _up)
		_position.ry()--;
	else if (_direction == _down)
		_position.ry()++;
}
