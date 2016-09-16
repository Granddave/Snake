#include "game.h"


Game::Game(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	setFixedWidth(W_WIDTH);
	setFixedHeight(W_HEIGHT);

	// Updates the game (e.g. keymaps, gamestates etc)
	_gameTimer = new QTimer(this);
	connect(_gameTimer, SIGNAL(timeout()), this, SLOT(update()));
	_gameTimer->start(5); // 16 

	// Updates the snake
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
	p.setBrush(Qt::lightGray);
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
	if (_gameSpeed > 10)
	_gameSpeed -= CHANGE_SPEED_CONSTANT;
	
	// Restarts timer to activate new speed
	_moveTimer->stop();
	_moveTimer->start(_gameSpeed);
}

void Game::update()
{
#if DEBUG_SPEED
	static bool plusWasPressed = 0;
	static bool minusWasPressed = 0;
#endif

	
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
		

		_gameSpeed = SNAKE_SPEED;
		_moveTimer->start(_gameSpeed);
		
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
	
		
#if DEBUG_SPEED
		if (_keys[Qt::Key_Plus] != plusWasPressed)
			speedUp();
		plusWasPressed = _keys[Qt::Key_Plus];

		if (_keys[Qt::Key_Minus] != minusWasPressed)
		{
			// Increase speed
			// Called when snake eats point
			
				_gameSpeed += CHANGE_SPEED_CONSTANT;

			// Restarts timer to activate new speed
			_moveTimer->stop();
			_moveTimer->start(_gameSpeed);
		}
		minusWasPressed = _keys[Qt::Key_Minus];
#endif



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
