#include "game.h"


Game::Game(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	setFixedWidth(W_WIDTH);
	setFixedHeight(W_HEIGHT);

	_gameTimer = new QTimer(this);
	connect(_gameTimer, SIGNAL(timeout()), this, SLOT(update()));
	_gameTimer->start(5); // 16 

	_moveTimer = new QTimer(this);
	connect(_moveTimer, SIGNAL(timeout()), this, SLOT(updatePlayground()));

	
	_gamestate = start;
}

Game::~Game()
{
	delete _gameTimer;
	delete _moveTimer;
	delete _snake;
}

void Game::paintEvent(QPaintEvent* e)
{
	QPainter p(this);

#if DEBUG_BLOCK_NUMBERS
	p.setBrush(Qt::gray);
	for (int i = 0; i < BLOCKS_HORI; i++)
	{
		p.drawRect(i * BLOCK_SIZE, 0, BLOCK_SIZE, BLOCK_SIZE);
		p.drawText(i*BLOCK_SIZE + 5, 15, QString::number(i));

	}
	for (int i = 0; i < BLOCKS_VERT; i++)
	{
		p.drawRect(0, i * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
		p.drawText(5, i * BLOCK_SIZE + 15, QString::number(i));

	}
#endif

	switch (int state = _gamestate)
	{
	case start:
		// Welcometext and howto
		p.drawText(W_WIDTH / 2, W_HEIGHT / 2, QString("SNAKE"));
		p.drawText(W_WIDTH / 2 - 35, W_HEIGHT / 2 + 15, QString("PRESS SPACE TO PLAY"));
		break;

	case play:
		paintPlayground(p);
		break;

	case gameover:
		paintPlayground(p);
		
		// Gameover text
		p.drawText(W_WIDTH / 2, W_HEIGHT / 2, QString("OUCH"));
		p.drawText(W_WIDTH / 2 - 60, W_HEIGHT / 2 + 15, QString("PRESS SPACE TO PLAY AGAIN"));
		break;

	default:
		break;
	}
}

// Paints e.g. snake, points, walls etc 
void Game::paintPlayground(QPainter& p) const
{
	_snake->paint(p);
}

void Game::speedUp()
{
	// Increase speed
	// Called when snake eats point
}

void Game::update()
{
	switch (int state = _gamestate)
	{
	// First time start
	case start:
		if (_keys[Qt::Key_Space])
			_gamestate = newGame;

		_snake = nullptr;
		break;

	// Initialize new game
	case newGame:
		if (_snake != nullptr) // if replay
			delete _snake;

		_currentDirection = right;
		_snake = new Snake(_currentDirection);
		
		_moveTimer->start(SNAKE_SPEED);
		
		_gamestate = play;
		break;

	// Start new game
	case play:
		// Update keymap
		if (_keys[Qt::Key_Right] || _keys[Qt::Key_D])
			_currentDirection = right;
		else if (_keys[Qt::Key_Left] || _keys[Qt::Key_A])
			_currentDirection = left;
		else if (_keys[Qt::Key_Up] || _keys[Qt::Key_W])
			_currentDirection = up;
		else if (_keys[Qt::Key_Down] || _keys[Qt::Key_S])
			_currentDirection = down;

		if (!_snake->isAlive())
			_gamestate = gameover;
		break;

	case gameover:
		_moveTimer->stop();
		if (_keys[Qt::Key_Space])
			_gamestate = newGame;
		break;
	default:
		break;
	}
	
	if (_keys[Qt::Key_R])
		_gamestate = newGame;

	if (_keys[Qt::Key_Escape])
		close(); // Exit game
	
	repaint();
}

void Game::updatePlayground()
{
	_snake->changeHeadDirection(_currentDirection);
	_snake->update();

	// Loop through all blocks and save in map.

	// Check collision?
}
