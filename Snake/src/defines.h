#pragma once

#include <QPainter>

#define W_WIDTH					800				
#define W_HEIGHT				3*W_WIDTH/4		// 4:3 aspect ratio

#define BLOCK_SIZE				20				// Size. 20 as block size and 
												// W_WIDTH = 800 gives 40*30 squares

#define SNAKE_SPEED				100				// Snake update in ms
#define SNAKE_START_LENGTH		10			
#define CHANGE_SPEED_CONSTANT	5

#define BLOCKS_HORI				W_WIDTH / BLOCK_SIZE
#define	BLOCKS_VERT				W_HEIGHT / BLOCK_SIZE

#define DEBUG_SPEED			1
#define DEBUG_BLOCK_NUMBERS 1

enum Dir { up, right, down, left };
enum GameState { start, newGame, play, gameover };
enum BlockTypes { empty, snake, wall, point };

struct Pos
{
	int x, y;
	Pos()
	{
		x = 0;
		y = 0;
	}

	Pos(int X, int Y) 
	{
		x = X;
		y = Y;
	}
	
	bool operator <(const Pos& rhs) const
	{
		if (x < rhs.x) { return true; }
		if (rhs.x < x) { return false; }

		if (y < rhs.y) { return true; }
		if (rhs.y < y) { return false; }

		return false;
	}

	bool operator==(const Pos& a) const
	{
		return (x == a.x && y == a.y);
	}

	Pos& operator=(const Pos& a)
	{
		x = a.x;
		y = a.y;
		return *this;
	}
};
