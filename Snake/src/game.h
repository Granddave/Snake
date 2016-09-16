#ifndef SNAKE_H
#define SNAKE_H

// Libraries/Dependencies
#include <QtWidgets/QMainWindow>
#include "GeneratedFiles/ui_snake.h"
#include "ui_snake.h"
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include <time.h> 

// Files and classes
#include "defines.h"
#include "snake.h"
#include "candy.h"

class Game : public QMainWindow
{
	Q_OBJECT

public:
	Game(QWidget *parent = 0);
	~Game();

	void paintEvent(QPaintEvent * e)	override;
	void paintPlayground(QPainter& p)	const;
	void keyReleaseEvent(QKeyEvent *e)	override	{ _keys[e->key()] = false; }
	void keyPressEvent(QKeyEvent* e)	override	{ _keys[e->key()] = true; }

	void speedUp();

private slots:
	void update();
	void updatePlayground();
	void spawnCandy();

private:
	Ui::SnakeClass ui;
	QTimer* _gameTimer;			// Key and gamestate timer
	QTimer* _playgroundTimer;	// Playground update timer 
	QTimer* _candyTimer;		// 

	QMap<int, bool> _keys;		// Keymap

	int _gamestate;
	int _gameSpeed;

	QMap<Pos, int> _playgroundBlocks;	// Keeps track of the playground
	Snake* _snake;
	QVector<Candy> _candies;
	int _currentDirection;
};

#endif // SNAKE_H
