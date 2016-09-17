#include "candy.h"

Candy::Candy()
{
}

Candy::Candy(Pos position) : Block(position)
{
	_texture = QPixmap("Resources/candy.png");
}

Candy::~Candy()
{
}

void Candy::paint(QPainter& painter) const
{
	painter.setBrush(QColor("#FFBBAA"));
	painter.drawRect(_position.x * BLOCK_SIZE, _position.y * BLOCK_SIZE, _size, _size);
}
