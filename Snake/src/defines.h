#pragma once

#include <QPainter>

#define PI						3.14159265359

#define W_WIDTH					800			
#define W_HEIGHT				(3*W_WIDTH/4)		// 4:3 aspect ratio

#define BLOCK_SIZE				(W_WIDTH / 40)	// Size. 20 as block size and 
												// W_WIDTH = 800 gives 40*30 squares

#define SNAKE_SPEED				100				// Snake update in ms
#define SNAKE_TOP_SPEED			30				// Top speed. 100 as start speed, 
#define CHANGE_SPEED_CONSTANT	2
#define SNAKE_START_LENGTH		15		

#define CANDY_SPAWN_NUMBER		5
#define CANDY_COLOR_SHIFT_WAVE_LENGTH	(pow(10, -3) * 3)
#define CANDY_COLOR_SHIFT_AMPLITUDE		(25)

#define BLOCKS_HORI				W_WIDTH / BLOCK_SIZE
#define BLOCKS_VERT				(W_HEIGHT) / BLOCK_SIZE

#define DEBUG_KEYSTROKES		1
#define DEBUG_BLOCK_NUMBERS		0

enum Dir { _up, _right, _down, _left };
enum GameState { start, initGame, play, gameover };



