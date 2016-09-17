#include "wall.h"

Wall::Wall()
{
	
}

Wall::Wall(QPoint position) : Block(position)
{
	
}

Wall::~Wall()
{
	
}

void Wall::paint(QPainter& painter) const
{
	painter.setBrush(QColor("#333333"));
	painter.drawRect(_position.x() * BLOCK_SIZE, _position.y() * BLOCK_SIZE, _size, _size);
}
