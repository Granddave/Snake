#pragma once

#include <QPixmap>

#include "defines.h"
#include "block.h"

class Candy : public Block
{
public:
	Candy();
	Candy(Pos position);
	~Candy();

	void paint(QPainter& painter) const override;


private:
	QPixmap _texture;
	Pos _position;
};