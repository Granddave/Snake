#pragma once

#include <QPainter>

#define W_WIDTH					800				
#define W_HEIGHT				3*W_WIDTH/4		// 4:3 aspect ratio

#define BLOCK_SIZE				20				// Size. 20 as block size and 
												// W_WIDTH = 800 gives 40*30 squares

#define SNAKE_SPEED				100				// Snake update in ms
#define SNAKE_TOP_SPEED			30				// Top speed. 100 as start speed, 
#define SNAKE_START_LENGTH		10			
#define CHANGE_SPEED_CONSTANT	2

#define BLOCKS_HORI				W_WIDTH / BLOCK_SIZE
#define BLOCKS_VERT				(W_HEIGHT) / BLOCK_SIZE

#define DEBUG_KEYSTROKES		1
#define DEBUG_BLOCK_NUMBERS		0

enum Dir { up, right, down, left };
enum GameState { start, initGame, play, gameover };
enum BlockTypes { empty, wall, candy };



