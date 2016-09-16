#pragma once

#include "defines.h"
#include "snakepart.h"
#include <QtCore/qvector.h>
#include <QPainter>

class Snake
{
public:
	Snake(int startDir);
	~Snake();

	void update();
	void paint(QPainter& painter);

	int getDirection(int p)	{ return _parts[p].getDir(); }
	Pos getPosition(int part) { return _parts[part].getPos(); }

	bool isAlive() const	{ return _alive;  }
	void changeHeadDirection(int dir);
	void grow();
	void shrink();

	void detectCollision();

private:
	int _length;
	int _speed;
	QVector<SnakePart> _parts;
	bool _alive;

	
};