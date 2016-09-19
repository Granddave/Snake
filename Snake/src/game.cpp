#include "game.h"
#include <time.h>	// for rand()

Game::Game(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	setFixedWidth(W_WIDTH);
	setFixedHeight(W_HEIGHT);

	srand(time(nullptr));

	// Updates the game (e.g. keymaps, gamestates etc)
	_gameTimer = new QTimer(this);
	connect(_gameTimer, SIGNAL(timeout()), this, SLOT(update()));
	_gameTimer->start(5); // 16 

	// Updates the snake
	_playgroundTimer = new QTimer(this);
	connect(_playgroundTimer, SIGNAL(timeout()), this, SLOT(updatePlayground()));


	_gamestate = start;
}

Game::~Game()
{
	delete _gameTimer;
	delete _playgroundTimer;
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
	QRect _rect;
	switch (_gamestate)
	{
	case start:
		// Welcometext and howto
		p.setBrush(QColor("#CCCCCC"));
		_rect = QRect(W_WIDTH / 2 - 80, W_HEIGHT / 2 - 80, 160, 60);
		p.drawRect(_rect);
		p.drawText(_rect, Qt::AlignCenter,
			"SNAKE \nPRESS SPACE TO PLAY");
		break;

	case play:
		paintPlayground(p);
		p.drawText(W_WIDTH - 45, 15, QString("Score:" + QString::number(_score)));
		break;

	case gameover:
		paintPlayground(p);
		
		p.setBrush(QColor("#CCCCCC"));
		_rect = QRect(W_WIDTH / 2 - 90, W_HEIGHT / 2 - 80, 180, 70);
		p.drawRect(_rect);
		p.drawText(_rect, Qt::AlignCenter,
			"OUCH \nTotal score: " + QString::number(_score) + "\nPRESS SPACE TO PLAY AGAIN");
		break;
	default:
		break;
	}
}

// Paints e.g. snake, points, walls etc 
void Game::paintPlayground(QPainter& p) const
{
	if (_candies.length() != 0)
	for (int i = 0; i < _candies.length(); i++)
		_candies[i].paint(p);
	
	_snake->paint(p);

	if (_walls.length() != 0)
	for (int i = 0; i < _walls.length(); i++)
		_walls[i].paint(p);
}

void Game::speedUp()
{
	// Increase speed
	// Called when snake eats point
	if (_gameSpeed >= SNAKE_TOP_SPEED)
		if (_gameSpeed < 50)
			_gameSpeed -= 1;	// to balance
		else
			_gameSpeed -= CHANGE_SPEED_CONSTANT;
		
	
	// Restarts timer to activate new speed
	_playgroundTimer->stop();
	_playgroundTimer->start(_gameSpeed);
}


void Game::update()
{
#if DEBUG_KEYSTROKES
	static bool plusWasPressed = 0;
	static bool minusWasPressed = 0;
	static bool oneWasPressed = 0;
	static bool twoWasPressed = 0;
	static bool pWasPressed = 0;
	static bool isPaused = 0;
#endif
	switch (_gamestate)
	{
	// First time start
	case start:
		if (_keys[Qt::Key_Space])
			_gamestate = initGame;

		_snake = nullptr;

		if (_walls.isEmpty())
			spawnWalls();
		break;

	// Initialize new game
	case initGame:
		// Clears everything (if replay)
		if (_snake != nullptr) 
			delete _snake;
		if (!_candies.isEmpty())
			_candies.clear();
		
		_score = 0;
		_currentDirection = _right;
		_snake = new Snake(_currentDirection);
		_playgroundTimer->start(_gameSpeed = SNAKE_SPEED);
		
		_gamestate = play;
		break;

	// Play game
	case play:
		// Update keymap
		if (_keys[Qt::Key_Right] || _keys[Qt::Key_D])		_currentDirection = _right;
		else if (_keys[Qt::Key_Left] || _keys[Qt::Key_A])	_currentDirection = _left;
		else if (_keys[Qt::Key_Up] || _keys[Qt::Key_W])		_currentDirection = _up;
		else if (_keys[Qt::Key_Down] || _keys[Qt::Key_S])	_currentDirection = _down;

		if (!_snake->isAlive())
			_gamestate = gameover;

		// Spawn candy in waves (5 at a time)
		if (_candies.isEmpty())
			for (int i = 0; i < CANDY_SPAWN_NUMBER; i++)
				spawnCandy();

#if DEBUG_KEYSTROKES
		if (_keys[Qt::Key_Plus] != plusWasPressed)
			speedUp();
		plusWasPressed = _keys[Qt::Key_Plus];

		if (_keys[Qt::Key_Minus] != minusWasPressed)
		{
			// Increase speed
			// Called when snake eats point
			
				_gameSpeed += CHANGE_SPEED_CONSTANT;

			// Restarts timer to activate new speed
			_playgroundTimer->stop();
			_playgroundTimer->start(_gameSpeed);
		}
		minusWasPressed = _keys[Qt::Key_Minus];
		
		if (_keys[Qt::Key_1] != oneWasPressed)
			_snake->grow();
		oneWasPressed = _keys[Qt::Key_1];

		if (_keys[Qt::Key_2] != twoWasPressed)
			_snake->shrink();
		twoWasPressed = _keys[Qt::Key_2];

		if (_keys[Qt::Key_P] != pWasPressed)
		if (isPaused)
		{
			_playgroundTimer->start(_gameSpeed);
			isPaused = false;
		}
		else
		{
			_playgroundTimer->stop();
			isPaused = true;
		}
		pWasPressed = _keys[Qt::Key_2];

#endif
		break;

	// Player lost
	case gameover:
		_playgroundTimer->stop();

		if (_keys[Qt::Key_Space])
			_gamestate = initGame;
		break;
	default:
		break;
	}

	// Replay
	if (_keys[Qt::Key_R])
	{
		//_gamestate = initGame;
		spawnCandy();
	}
	// Exit game
	if (_keys[Qt::Key_Escape])
		close(); 

	repaint();
}

// Updates all blocks
void Game::updatePlayground()
{
	// Update direction and movement of the snake
	_snake->setHeadDirection(_currentDirection);
	_snake->detectCollision();
	
	// Snake head against wall
	for (int i = 1; i < _walls.length(); i++) // Skipping first because head is i = 0
	{
		if (((_snake->getPos(0).x() + 1 == _walls[i].getPos().x() && _snake->getDirection(0) == _right ||
			  _snake->getPos(0).x() - 1 == _walls[i].getPos().x() && _snake->getDirection(0) == _left) &&
			  _snake->getPos(0).y() == _walls[i].getPos().y()) ||

			((_snake->getPos(0).y() + 1 == _walls[i].getPos().y() && _snake->getDirection(0) == _down ||
			  _snake->getPos(0).y() - 1 == _walls[i].getPos().y() && _snake->getDirection(0) == _up) &&
			  _snake->getPos(0).x() == _walls[i].getPos().x()))
		{
			_snake->kill();
		}
	}

	// Check snake collision with candy   
	for (int i = 0; i < _candies.length(); i++)
		if (_candies[i].getPos() == _snake->getPos(0))
			eatCandy(i);

	_snake->update();
}

void Game::spawnWalls()
{
	// Map 1
	for (int i = 0; i < 20; i++)
	{
		QPoint pos = QPoint(10 + i, 4);
			_walls.append(Wall(pos));
	}
	for (int i = 0; i < 10; i++)
	{
		QPoint pos = QPoint(10, 5 + i);
		_walls.append(Wall(pos));
	}
	for (int i = 0; i < 10; i++)
	{
		QPoint pos = QPoint(29, 5 + i);
		_walls.append(Wall(pos));
	}
	for (int i = 0; i < 7; i++)
	{
		QPoint pos = QPoint(29 - i, 15);
		_walls.append(Wall(pos));
	}
	for (int i = 0; i < 7; i++)
	{
		QPoint pos = QPoint(10 + i, 15);
		_walls.append(Wall(pos));
	}
}


// Spawns a piece of candy on free space
void Game::spawnCandy()
{
	bool onFreeSpace = true;
	QPoint pos;
	do
	{
		onFreeSpace = true;
		pos = QPoint(rand() % BLOCKS_HORI, rand() % BLOCKS_VERT);
		
		// Check if the snake occupies pos
		for (int i = 0; i < _snake->getLenght(); i++)
			if (pos == _snake->getPos(i))
				onFreeSpace = false;

		// Check if a wall occupies pos
		for (int i = 0; i < _walls.length(); i++)
			if (pos == _walls[i].getPos())
				onFreeSpace = false;
		
		// Check if a candy occupies pos
		for (int i = 0; i < _candies.length(); i++)
			if (pos == _candies[i].getPos())
				onFreeSpace = false;

	} while (!onFreeSpace);
	_candies.append(Candy(pos));
}


void Game::eatCandy(int candy)
{
	_candies.remove(candy);
	_score++;
	_snake->grow();
	speedUp();
}

