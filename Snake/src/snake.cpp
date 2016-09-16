#include "Snake.h"


Snake::Snake(int startDir) : _length(SNAKE_START_LENGTH)
{
	for (int i = 0; i < SNAKE_START_LENGTH; i++)
		_parts.push_back(SnakePart(BLOCKS_HORI / 2 - i, BLOCKS_VERT / 2, startDir));

	_alive = true;
	_speed = SNAKE_SPEED;
}

Snake::~Snake()
{

}

void Snake::update()
{
	detectCollision();

	if (!_alive)
		return;

	// Move snake parts
	for (int i = 0; i < _parts.length(); i++)
		_parts[i].move();

	// Change direction of snake parts
 	for (int i = _parts.length(); i != 1; i--)
		_parts[i-1].changeDir(_parts[i-2].getDir());	// Starts at _parts[i-1] because count starts at 0 in the vector.
}

void Snake::detectCollision()
{
	// Check collision with wall
	if (getDirection(0) == left  && _parts[0]._position.x == 0 ||
		getDirection(0) == right && _parts[0]._position.x == BLOCKS_HORI - 1||
		getDirection(0) == up    && _parts[0]._position.y == 0 ||
		getDirection(0) == down  && _parts[0]._position.y == BLOCKS_VERT - 1
		)
	{
		_alive = false;
	}

	// TODO
	// Check the heads position against snakeparts

}
void Snake::paint(QPainter& painter)
{
	for (int i = 0; i < _parts.length(); i++)
		_parts[i].paint(painter);
}

void Snake::changeHeadDirection(int dir)
{
	if (_parts[0].getDir() == up    && dir != down  ||
		_parts[0].getDir() == down  && dir != up    ||
		_parts[0].getDir() == left  && dir != right ||
		_parts[0].getDir() == right && dir != left)
	{
		_parts[0].changeDir(dir);
	}
}

