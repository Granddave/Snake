#include "game.h"

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

	_candyTimer = new QTimer(this);
	connect(_candyTimer, SIGNAL(timeout()), this, SLOT(updatePlayground()));

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

	switch (_gamestate)
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

	if (_candies.length() != 0)
	for (int i = 0; i < _candies.length(); i++)
		_candies[i].paint(p);
}

void Game::speedUp()
{
	// Increase speed
	// Called when snake eats point
	if (_gameSpeed > 10)
	_gameSpeed -= CHANGE_SPEED_CONSTANT;
	
	// Restarts timer to activate new speed
	_playgroundTimer->stop();
	_playgroundTimer->start(_gameSpeed);
}

void Game::update()
{
	int a, b;
#if DEBUG_KEYSTROKES
	static bool plusWasPressed = 0;
	static bool minusWasPressed = 0;
	static bool oneWasPressed = 0;
	static bool twoWasPressed = 0;
#endif
	switch (_gamestate)
	{
	// First time start
	case start:
		if (_keys[Qt::Key_Space])
			_gamestate = newGame;

		_snake = nullptr;
		break;

	// Initialize new game
	case newGame:
		// Clears everything 
		if (_snake != nullptr) // if replay
			delete _snake;
		if (!_candies.isEmpty())
			_candies.clear();
		

		_currentDirection = right;
		_snake = new Snake(_currentDirection);
		
		_playgroundTimer->start(_gameSpeed = SNAKE_SPEED);
		
		_candies.append(Candy(Pos(rand() % BLOCKS_HORI, rand() % BLOCKS_VERT)));

		_gamestate = play;
		break;

	// Play game
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


#endif
		break;

	// Player lost
	case gameover:
		_playgroundTimer->stop();

		if (_keys[Qt::Key_Space])
			_gamestate = newGame;
		break;
	default:
		break;
	}

	// Replay
	if (_keys[Qt::Key_R])
		_gamestate = newGame;	

	// Exit game
	if (_keys[Qt::Key_Escape])
		close(); 

	repaint();
}

void Game::updatePlayground()
{
	// Loop through all blocks and save in map.
	// Add walls to map

	// Add points to map
	for (int i = 0; i < _candies.length(); i++)
	{
		Pos temp = _candies[i].getPos();
		_playgroundBlocks[Pos(temp)] = candy;
	}

	// Updates snake
	_snake->setHeadDirection(_currentDirection);
	_snake->update();
	
	// Check collision with wall and candy? 
	/*
	for (int i = 0; i < BLOCKS_HORI; i++)
	for (int j = 0; j < BLOCKS_VERT; j++)
		{
			if (_playgroundBlocks[Pos(i,j)] == candy)			
		}
	*/
}

void Game::spawnCandy()
{
	_candies.append(Candy(Pos(rand() % BLOCKS_HORI - 1, rand() % BLOCKS_VERT - 1)));
}