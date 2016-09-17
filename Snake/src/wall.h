#pragma once

#include <QPixmap>

#include "defines.h"
#include "block.h"

class Wall : public Block
{
public:
	Wall();
	Wall(QPoint position);
	~Wall();

	void paint(QPainter& painter) const override;

private:
};