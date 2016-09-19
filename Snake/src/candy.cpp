#include "candy.h"
#include <QTime>
#include <iostream>
#include <qDebug>

Candy::Candy()
{
}

Candy::Candy(QPoint position) : Block(position), _colorShift((double)rand()/RAND_MAX * PI)
{
	_texture = QPixmap("Resources/candy.png");
}
 
Candy::~Candy()
{
}

void Candy::paint(QPainter& painter) const
{
	//painter.setBrush(QColor("#FFBBAA"));
#if 1
	QTime c = QTime().addSecs(20);
	c.start();
	int s = sin((double)c.msecsSinceStartOfDay() * CANDY_COLOR_SHIFT_WAVE_LENGTH + _colorShift) * CANDY_COLOR_SHIFT_AMPLITUDE;
	//std::cout << "ms:" << ms << "	sin:" << s << std::endl;
	//qDebug() << "ms:" << ms << "	ms/1000" << ms / 1000 << "	sin:" << s;
	painter.setBrush(QColor(0xFF, 187+s, 170+s, 255)); 
#else
	painter.setBrush(QColor(0xFF, 0xBB, 0xAA, 255));
#endif
	painter.drawRect(_position.x() * BLOCK_SIZE, _position.y() * BLOCK_SIZE, _size, _size);
}
