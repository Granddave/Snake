#ifndef SNAKE_H
#define SNAKE_H

#include <QtWidgets/QMainWindow>
#include "GeneratedFiles/ui_snake.h"
#include "ui_snake.h"
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>

#include "defines.h"
#include "snake.h"

class Game : public QMainWindow
{
	Q_OBJECT

public:
	Game(QWidget *parent = 0);
	~Game();

	void paintEvent(QPaintEvent * e) override;
	void paintPlayground(QPainter& p) const;

	void keyReleaseEvent(QKeyEvent *e){ _keys[e->key()] = false; }
	void keyPressEvent(QKeyEvent* e){ _keys[e->key()] = true; }

	void speedUp();


	private slots:
	void update();
	void updatePlayground();

private:
	Ui::SnakeClass ui;
	QTimer* _gameTimer;		// Key and gamestate timer
	QTimer* _moveTimer;		// Playground update timer 
	QMap<int, bool> _keys;	// Keymap

	QMap<Pos, int> _blockIsOccupied;	// 


	int _gamestate;
	int _gameSpeed;

	Snake* _snake;
	int _currentDirection;
};

#endif // SNAKE_H
