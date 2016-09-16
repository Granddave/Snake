#pragma once

#include "defines.h"
#include "snakepart.h"
#include <QtCore/qvector.h>

class Snake
{
public:
	Snake(int startDir);
	~Snake();

	void update();
	void paint(QPainter& painter);

	void grow();
	void shrink();
	void kill();
	bool detectCollision();
	
	int getDirection(int p)		{ return _parts[p].getDir(); }
	Pos getPosition(int part)	{ return _parts[part].getPos(); }
	int getLenght() const		{ return _parts.length(); }
	bool isAlive() const		{ return _alive;  }

	void setHeadDirection(int dir);

private:
	int _length;
	QVector<SnakePart> _parts;
	bool _alive;
};