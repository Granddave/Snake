#pragma once

#include <QPixmap>

#include "defines.h"
#include "block.h"

class Candy : public Block
{
public:
	Candy();
	Candy(QPoint position);
	~Candy();

	void paint(QPainter& painter) const override;


private:
	QPixmap _texture;
};