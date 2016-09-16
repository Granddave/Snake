#pragma once

#define W_WIDTH				800				
#define W_HEIGHT			3*W_WIDTH/4		// 4:3 aspect ratio

#define BLOCK_SIZE			20				// Size. 20 as block size and 
											// W_WIDTH = 800 gives 40*30 squares
#define SNAKE_SPEED			100				// Snake update in ms
#define SNAKE_START_LENGTH	6			

#define BLOCKS_HORI			W_WIDTH / BLOCK_SIZE
#define	BLOCKS_VERT			W_HEIGHT / BLOCK_SIZE


#define DEBUG_BLOCK_NUMBERS 1

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
};

enum Dir { up, right, down, left };
enum GameState { start, newGame, play, gameover };
enum BlockTypes { empty, snake, wall, point };