#include "Pacman.h"
#include "Ghost.h"
#include <sstream>

void Pacman::LoadPacmanContent()
{
	// Load Pacman
	_pacmanTexture = new Texture2D();
	_pacmanTexture->Load("Textures/Beeman.tga", false);
	_pacmanPosition = new Vector2(350.0f, 350.0f);
	_pacmanSourceRect = new Rect(0.0f, 0.0f, 32, 32);
}

Pacman::~Pacman()
{
	delete _pacmanTexture;
	delete _pacmanSourceRect;
}

Pacman::Pacman(Input::Keys up, Input::Keys down, Input::Keys left, Input::Keys right, Input::Keys leftShift) :  _cPacmanSpeed(0.1f), _cPacmanFrameTime(250)
{
	_pacmanCurrentFrameTime = 0;
	_pacmanFrame = 0;
	_cherryMult = 1.0f;
	_levelHandicap = 0.0f;
	_pacmanSpeedMultiplier = (3.0f - _levelHandicap);
	_up = up;
	_down = down;
	_left = left;
	_right = right;
	_leftShift = leftShift;
	dead = false;
	LoadPacmanContent();
}

void Pacman::Update(int elapsedTime, Input::KeyboardState* state)
{
	this->Input(elapsedTime, state);
	_pacmanCurrentFrameTime += elapsedTime;
	if (_pacmanCurrentFrameTime > _cPacmanFrameTime)
	{
		_pacmanFrame++;
		if (_pacmanFrame >= 2)
		{
			_pacmanFrame = 0;
		}
		_pacmanCurrentFrameTime = 0;
	}
	_pacmanSourceRect->X = _pacmanSourceRect->Width * _pacmanFrame;
	_pacmanSourceRect->Y = _pacmanSourceRect->Height * _direction;
	CheckViewportCollision();
}

void Pacman::Draw(int elapsedTime)
{
	if (!dead)
	{
		SpriteBatch::Draw(_pacmanTexture, _pacmanPosition, _pacmanSourceRect, Vector2::Zero, 1.0f, 0.0f, Color::White, SpriteEffect::NONE); // Draws Pacman
	}
}

void Pacman::CheckViewportCollision()
{
	// Checks if Pacman is trying to disappear
	if (_pacmanPosition->X + _pacmanSourceRect->Width > Graphics::GetViewportWidth())
	{
		// Pacman hit right wall - reset his position
		_pacmanPosition->X = 0;
	}
	if (_pacmanPosition->X < 0)
	{
		// Pacman hit left wall - reset his position
		_pacmanPosition->X = Graphics::GetViewportWidth() - _pacmanSourceRect->Width;
	}
	if (_pacmanPosition->Y < 0)
	{
		// Pacman hit left wall - reset his position
		_pacmanPosition->Y = Graphics::GetViewportHeight() - _pacmanSourceRect->Width;
	}
	if (_pacmanPosition->Y > Graphics::GetViewportHeight() - _pacmanSourceRect->Width)
	{
		// Pacman hit left wall - reset his position
		_pacmanPosition->Y = 0;
	}
}


void Pacman::Input(int elapsedTime, Input::KeyboardState* state)
{
	_pacmanSpeed = _cPacmanSpeed * elapsedTime * _pacmanSpeedMultiplier * _cherryMult;
	// Checks if D key is pressed
	if (state->IsKeyDown(_right))
	{
		_pacmanPosition->X += _pacmanSpeed; //Moves Pacman across X axis
		_direction = 0;
	}
	// Checks if A key is pressed
	else if (state->IsKeyDown(_left))
	{
		_pacmanPosition->X -= _pacmanSpeed; //Moves Pacman across X axis
		_direction = 2;
	}
	// Checks if W key is pressed
	else if (state->IsKeyDown(_up))
	{
		_pacmanPosition->Y -= _pacmanSpeed; //Moves Pacman across Y axis
		_direction = 3;
	}
	// Checks if S key is pressed
	else if (state->IsKeyDown(_down))
	{
		_pacmanPosition->Y += _pacmanSpeed; //Moves Pacman across Y axis
		_direction = 1;
	}
	if (state->IsKeyDown(_leftShift))
	{
		_pacmanSpeedMultiplier = (4.0f - _levelHandicap);
	}
	else
	{
		_pacmanSpeedMultiplier = (3.0f - _levelHandicap);
	}
}