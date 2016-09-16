#include "Snake.h"


Snake::Snake(int startDir) : _length(SNAKE_START_LENGTH)
{
	for (int i = 0; i < SNAKE_START_LENGTH; i++)
		_parts.push_back(SnakePart(BLOCKS_HORI / 2 - i, BLOCKS_VERT / 2, startDir));

	_alive = true;
}

Snake::~Snake()
{

}

void Snake::update()
{
	if (detectCollision())
	{
		_alive = false;
		return;	// so snake doesn't move when dead
	}

	// Move snake parts
	for (int i = 0; i < _parts.length(); i++)
		_parts[i].move();

	// Change direction of snake parts
 	for (int i = _parts.length(); i != 1; i--)
		_parts[i-1].setDir(_parts[i-2].getDir());	// Starts at _parts[i-1] because count starts at 0 in the vector.
}

void Snake::paint(QPainter& painter)
{
	for (int i = 0; i < _parts.length(); i++)
		_parts[i].paint(painter);
}

void Snake::grow()
{
}

void Snake::shrink()
{
}

bool Snake::detectCollision()
{
	// Collision with wall
	if (getDirection(0) == left  && _parts[0]._position.x == 0 ||
		getDirection(0) == right && _parts[0]._position.x == BLOCKS_HORI - 1||
		getDirection(0) == up    && _parts[0]._position.y == 0 ||
		getDirection(0) == down  && _parts[0]._position.y == BLOCKS_VERT - 1
		)
	{
		return true;
	}

	// Snake head against body
	for (int i = 1; i < _parts.length(); i++) // Skipping first because head is i = 0
	{
		if(((_parts[0].getPos().x + 1 == _parts[i].getPos().x && _parts[0].getDir() == right ||
			 _parts[0].getPos().x - 1 == _parts[i].getPos().x && _parts[0].getDir() == left) && 
			 _parts[0].getPos().y == _parts[i].getPos().y) || 

			(_parts[0].getPos().y + 1 == _parts[i].getPos().y && _parts[0].getDir() == down	|| 
			 _parts[0].getPos().y - 1 == _parts[i].getPos().y && _parts[0].getDir() == up)	&& 
			 _parts[0].getPos().x == _parts[i].getPos().x)
		{
			return true;
		}
	}
	return false;
}

void Snake::setHeadDirection(int dir)
{
	if (_parts[0].getDir() == up    && dir != down  ||
		_parts[0].getDir() == down  && dir != up    ||
		_parts[0].getDir() == left  && dir != right ||
		_parts[0].getDir() == right && dir != left)
	{
		_parts[0].setDir(dir);
	}
}

