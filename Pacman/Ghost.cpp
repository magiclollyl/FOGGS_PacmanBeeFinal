#include "Ghost.h"
#include "Pacman.h"

void Ghost::LoadGhostContent()
{
	// Load Ghost
	_ghostTexture = new Texture2D();
	if (_colour == 0)
	{
		_ghostTexture->Load("Textures/GhostBird.png", true);
	}
	else if (_colour == 1)
	{
		_ghostTexture->Load("Textures/GhostBlackBird.png", true);
	}
	else if (_colour == 2)
	{
		_ghostTexture->Load("Textures/GhostSeagull.png", true);
	}
	else if (_colour == 3)
	{
		_ghostTexture->Load("Textures/GhostCrowBird.png", true);
	}
	_ghostPosRect = new Rect(rand() % (Graphics::GetViewportWidth() - 20), rand() % (Graphics::GetViewportHeight() - 20), 20, 20);
	_ghostSourceRect = new Rect(0.0f, 0.0f, 20, 20);
	_ghostFollowDirection = new Vector2(0.0f, 0.0f);
}

Ghost::~Ghost()
{
	delete _ghostPosRect;
	delete _ghostTexture;
}

Ghost::Ghost() : _cGhostFrameTime(500)
{
	_ghostDirection = 0; 
	_ghostSpeed = 0.1f;
	_xORy = rand() % 3;
	_colour = rand() % 3;
	LoadGhostContent();
	whereIsPacman = new Vector2(0, 0);
}

void Ghost::UpdateGhosts(int elapsedTime, Vector2* pacmanPosition)
{
	whereIsPacman = pacmanPosition;
	_ghostFollowDirection->X = pacmanPosition->X - _ghostPosRect->X;
	_ghostFollowDirection->Y = pacmanPosition->Y - _ghostPosRect->Y;
	if (abs(_ghostFollowDirection->X) > abs(_ghostFollowDirection->Y))
	{
		if (_ghostFollowDirection->X < 0)
		{
			_ghostDirection = 2;
		}
		else
		{
			_ghostDirection = 0;
		}
	}
	else
	{
		if (_ghostFollowDirection->Y < 0)
		{
			_ghostDirection = 3;
		}
		else
		{
			_ghostDirection = 1;
		}
	}
	if (_ghostDirection == 0)
	{
		_ghostPosRect->X += _ghostSpeed * elapsedTime;
		_ghostSourceRect->Y = _ghostSourceRect->Height * 2;
	}
	else if (_ghostDirection == 1)
	{
		_ghostPosRect->Y += _ghostSpeed * elapsedTime;
	}
	else if (_ghostDirection == 2)
	{
		_ghostPosRect->X -= _ghostSpeed * elapsedTime;
		_ghostSourceRect->Y = _ghostSourceRect->Height;
	}
	else if (_ghostDirection == 3)
	{
		_ghostPosRect->Y -= _ghostSpeed * elapsedTime;
	}

	_ghostCurrentFrameTime += elapsedTime;
	if (_ghostCurrentFrameTime > _cGhostFrameTime)
	{
		_ghostFrameCount++;
		if (_ghostFrameCount >= 2)
			_ghostFrameCount = 0;
		_ghostCurrentFrameTime = 0;
	}

	//_ghostSourceRect->Y = _ghostSourceRect->Height * _ghostDirection;
	_ghostSourceRect->X = _ghostSourceRect->Width * _ghostFrameCount;
}

void Ghost::Draw(int elapsedTime)
{
	SpriteBatch::Draw(_ghostTexture, _ghostPosRect, _ghostSourceRect, Vector2::Zero, 1.0f, 0.0f, Color::White, SpriteEffect::NONE);
}