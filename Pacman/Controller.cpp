#include "Controller.h"
#include <sstream>
#include "Munchie.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Cherry.h"
#include <time.h>
#include "Fountain.h"

void Controller::LoadContent()
{
	// Set string position
	_stringPosition = new Vector2(10.0f, 25.0f);

	// Set Menu Paramters
	_menuBackground = new Texture2D();
	_menuBackground->Load("Textures/Transparency.png", true);
	_menuRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());
	_menuStringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f - 75.0f, Graphics::GetViewportHeight() / 2.0f);

	_mainBackground = new Texture2D();
	_mainBackground->Load("Textures/pacmanBackgroundPath.png", true);

	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		_munchie[i] = new Munchie(Input::Keys::R);
	}
	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		_ghosts[i] = new Ghost();
	}
	_pacman = new Pacman(Input::Keys::W, Input::Keys::S, Input::Keys::A, Input::Keys::D, Input::Keys::LEFTSHIFT);
	_cherry = new Cherry();
	_fountain = new Fountain();
	_pop = new SoundEffect();
	_pop->Load("Sounds/pop.wav");
	_birds = new SoundEffect();
	_birds->Load("Sounds/gameOverBirds.wav");
	_levelUp = new SoundEffect();
	_levelUp->Load("Sounds/levelUp.wav");
	_cherryGet = new SoundEffect();
	_cherryGet->Load("Sounds/cherryGet.wav");
	_gameWin = new SoundEffect();
	_gameWin->Load("Sounds/gameWin.wav");
	_splash = new SoundEffect();
	_splash->Load("Sounds/splash.wav");
}

Controller::Controller(int argc, char* argv[]) : Game(argc, argv)
{
	srand(time(NULL));

	_paused = false;
	_pKeyDown = false;
	_start = true;
	_gameOver = false;
	_gameWon = false;
	_playerScore = 0;
	_playerLevel = 1;

	//Initialise important Game aspects
	Audio::Initialise();
	Graphics::Initialise(argc, argv, this, 1024, 768, false, 25, 25, "Pacman", 60);
	Input::Initialise();

	// Start the Game Loop - This calls Update and Draw in game loop
	Graphics::StartGameLoop();
}

Controller::~Controller()
{
	delete _stringPosition;
	delete _pop;
	delete _mainBackground;
	delete _menuBackground;
	delete _menuRectangle;
}

void Controller::Update(int elapsedTime)
{
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();
	Input::MouseState* mouseState = Input::Mouse::GetState();
	if (keyboardState->IsKeyDown(Input::Keys::SPACE))
	{
		_start = false;
	}
	CheckPaused(keyboardState, Input::Keys::P);
	Input(elapsedTime, mouseState);
	DeadPacman();
	EatMunchie();
	EatCherry();
	WetBee();
	LevelUp();
	if (!_paused && !_start && !_gameOver && !_gameWon)
	{
		for (int i = 0; i < MUNCHIECOUNT; i++)
		{
			_munchie[i]->Update(elapsedTime, keyboardState);
		}
		if (!(_pacman->dead))
		{
			_pacman->Update(elapsedTime, keyboardState);
		}
		for (int i = 0; i < GHOSTCOUNT; i++)
		{
			_ghosts[i]->UpdateGhosts(elapsedTime, _pacman->_pacmanPosition);

		}
		_cherry->Update(elapsedTime);
		_fountain->UpdateFountain(elapsedTime);
	}
	if (waitTime != 0)
	{
		WaitTime();
	}
	if (_gameOver || _gameWon)
	{
		Restart(keyboardState);
	}
}


void Controller::Draw(int elapsedTime)
{
	// Allows us to easily create a string
	std::stringstream stream;
	stream << "Pacman X: " << _pacman->_pacmanPosition->X << " Y: " << _pacman->_pacmanPosition->Y << "				Score: " << _playerScore << "          Level: " << _playerLevel << "						Press R to grow more flowers!";

	SpriteBatch::BeginDraw(); // Starts Drawing
	SpriteBatch::Draw(_mainBackground, _menuRectangle, nullptr);
	
	SpriteBatch::DrawString(stream.str().c_str(), _stringPosition, Color::Black); // Draws String
	
	_fountain->DrawFountain(elapsedTime);
	_pacman->Draw(elapsedTime);
	_cherry->Draw(elapsedTime);
	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		_munchie[i]->Draw(elapsedTime);
	}
	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		_ghosts[i]->Draw(elapsedTime);
	}
	if (_start)
	{
		std::stringstream menuStream; menuStream << "SPACE to start!";
		SpriteBatch::Draw(_menuBackground, _menuRectangle, nullptr); SpriteBatch::DrawString(menuStream.str().c_str(), _menuStringPosition, Color::White);
	}

	if (_paused)
	{
		std::stringstream menuStream; menuStream << "PAUSED!";
		SpriteBatch::Draw(_menuBackground, _menuRectangle, nullptr); SpriteBatch::DrawString(menuStream.str().c_str(), _menuStringPosition, Color::White);
	}

	if (_gameOver)
	{
		std::stringstream menuStream; menuStream << "GAME OVER! Press G to restart!";
		SpriteBatch::Draw(_menuBackground, _menuRectangle, nullptr); SpriteBatch::DrawString(menuStream.str().c_str(), _menuStringPosition, Color::White);
	}

	if (_gameWon)
	{
		std::stringstream menuStream; menuStream << "You Win! Press G to restart!";
		SpriteBatch::Draw(_menuBackground, _menuRectangle, nullptr); SpriteBatch::DrawString(menuStream.str().c_str(), _menuStringPosition, Color::White);
	}

	SpriteBatch::EndDraw(); // Ends Drawing
}

void Controller::CheckPaused(Input::KeyboardState* state, Input::Keys pauseKey)
{
	if (state->IsKeyDown(Input::Keys::P) && !_pKeyDown)
	{
		_pKeyDown = true;
		_paused = !_paused;
	}
	if (state->IsKeyUp(Input::Keys::P))
	{
		_pKeyDown = false;
	}
}


bool Controller::CollisionCheck(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2)
{
	int left1 = x1;
	int left2 = x2;
	int right1 = x1 + width1;
	int right2 = x2 + width2;
	int top1 = y1;
	int top2 = y2;
	int bottom1 = y1 + height1;
	int bottom2 = y2 + height2;
	if (bottom1 < top2)
		return false;
	if (top1 > bottom2)
		return false;
	if (right1 < left2)
		return false;
	if (left1 > right2)
		return false;

	return true;
}

void Controller::Input(int elapsedTime, Input::MouseState* mouseState)
{
	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		if (mouseState->RightButton == Input::ButtonState::PRESSED)
		{
			if (CollisionCheck(mouseState->X, mouseState->Y, 16, 16, _munchie[i]->_munchiePosition->X, _munchie[i]->_munchiePosition->Y, 12, 12))
			{
				_munchie[i]->_munchiePosition->X = rand() % Graphics::GetViewportWidth();
				_munchie[i]->_munchiePosition->Y = rand() % Graphics::GetViewportHeight();
			}
		}
	}
}

void Controller::DeadPacman()
{
	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		if (CollisionCheck(_pacman->_pacmanPosition->X, _pacman->_pacmanPosition->Y, 32, 32, _ghosts[i]->_ghostPosRect->X, _ghosts[i]->_ghostPosRect->Y, 20, 20))
		{
			Audio::Play(_birds);
			_pacman->_pacmanPosition->X = 1000;
			_pacman->_pacmanPosition->Y = 1000;
			_pacman->dead = true;
			_gameOver = true;
		}
	}
}

void Controller::EatMunchie()
{
	for (int i = 0; i < MUNCHIECOUNT; i++)
		if (CollisionCheck(_pacman->_pacmanPosition->X, _pacman->_pacmanPosition->Y, 32, 32, _munchie[i]->_munchiePosition->X, _munchie[i]->_munchiePosition->Y, 12, 12))
		{
			_playerScore += 1;
			_munchie[i]->_munchiePosition->X = 2000;
			_munchie[i]->_munchiePosition->Y = 2000;
			Audio::Play(_pop);
		}
}

void Controller::EatCherry()
{
	if (CollisionCheck(_pacman->_pacmanPosition->X, _pacman->_pacmanPosition->Y, 32, 32, _cherry->_cherryPosition->X, _cherry->_cherryPosition->Y, 32, 32))
	{
		_playerScore += 10;
		Audio::Play(_cherryGet);
		_cherry->_cherryPosition->X = 2000;
		_cherry->_cherryPosition->Y = 2000;
		_cherry->Randomise();
		_pacman->_cherryMult = 2.0f;
		WaitTime();
	}
}

void Controller::WetBee()
{
	if (CollisionCheck(_pacman->_pacmanPosition->X, _pacman->_pacmanPosition->Y, 32, 32, _fountain->_fountainPosition->X, _fountain->_fountainPosition->Y, 130, 125))
	{
		_playerScore -= 1;
		Audio::Play(_splash);
	}
}

void Controller::WaitTime()
{
	if (waitTime == 150)
	{
		_pacman->_cherryMult = 1.0f;
		waitTime = 0;
	}
	else
	{
		waitTime += 1;
	}
}

void Controller::Restart(Input::KeyboardState* keyboardState)
{
	if (keyboardState->IsKeyDown(Input::Keys::G))
	{
		_pacman->_pacmanPosition->X = 350;
		_pacman->_pacmanPosition->Y = 350;
		_gameOver = false;
		for (int i = 0; i < GHOSTCOUNT; i++)
		{
			_ghosts[i]->_ghostPosRect->X = rand() % (Graphics::GetViewportWidth() - 20);
			_ghosts[i]->_ghostPosRect->Y = rand() % (Graphics::GetViewportHeight() - 20);
		}
		for (int i = 0; i < MUNCHIECOUNT; i++)
		{
			_munchie[i]->_random = true;
		}
		_pacman->dead = false;
		_pacman->_levelHandicap = 0.0f;
		_playerScore = 0;
		_playerLevel = 1;
		_gameWon = false;
		_start = true;
	}
}

void Controller::LevelUp()
{
	if (_playerLevel == 1 && _playerScore >= 30)
	{
		Audio::Play(_levelUp);
		_playerLevel++;
		for (int i = 0; i < MUNCHIECOUNT; i++)
		{
			_munchie[i]->_random = true;
		}
		_pacman->_levelHandicap = 1.0f;
		_playerScore = 0;
	}
	if (_playerLevel == 2 && _playerScore >= 60)
	{
		Audio::Play(_levelUp);
		_playerLevel++;
		for (int i = 0; i < MUNCHIECOUNT; i++)
		{
			_munchie[i]->_random = true;
		}
		for (int i = 0; i < GHOSTCOUNT; i++)
		{
			_ghosts[i]->_ghostSpeed == 0.2f;
		}
		_pacman->_levelHandicap = 2.0f;
		_playerScore = 0;
	}
	if (_playerLevel == 3 && _playerScore >= 100)
	{
		if (_playerScore >= 100)
		{
			Audio::Play(_gameWin);
		}
		_playerScore = 0;
		_gameWon = true;
	}
}
