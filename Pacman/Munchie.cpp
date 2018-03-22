#include "Munchie.h"
#include <sstream>
#include "Controller.h"
#include "WinUser.h"
#include <iostream>

void Munchie::LoadMunchieContent()
{
	// Load Munchie
	_munchieTexture = new Texture2D();
	_munchieTexture->Load("Textures/munchieFlower.png", true);
	_munchieRect = new Rect(0.0f, 0.0f, 12, 12);
	if (spawnLocation == 1)
	{
		_munchiePosition = new Vector2(rand() % 340, rand() % 255);
	}
	if (spawnLocation == 2)
	{
		_munchiePosition = new Vector2(rand() % Graphics::GetViewportWidth() + 680, rand() % 255);
	}
	if (spawnLocation == 3)
	{
		_munchiePosition = new Vector2(rand() % 340, rand() % Graphics::GetViewportHeight() + 510);
	}
	if (spawnLocation == 4)
	{
		_munchiePosition = new Vector2(rand() % Graphics::GetViewportWidth() + 680, rand() % Graphics::GetViewportHeight() + 510);
	}
}

Munchie::~Munchie()
{
	delete _munchieRect;
	delete _munchieTexture;
	delete _munchiePosition;
}

Munchie::Munchie(Input::Keys rButton) :  _cMunchieFrameTime(500)
{
	_munchieFrameCount = 0;
	_munchieCurrentFrameTime = 0;
	_rButton = rButton;
	_rKeyDown = false;
	_random = false;
	spawnLocation = rand() % 4 + 1;
	LoadMunchieContent();
}

void Munchie::Update(int elapsedTime, Input::KeyboardState* keyboardState)
{
	CheckRandom(keyboardState);
	UpdateMunchie(elapsedTime);
	if (_random)
	{
		spawnLocation = rand() % 4 + 1;
		if (spawnLocation == 1)
		{
			_munchiePosition->X = rand() % 340;
			_munchiePosition->Y = rand() % 255;
		}
		if (spawnLocation == 2)
		{
			_munchiePosition->X = rand() % 768 + 680;
			_munchiePosition->Y = rand() % 255;
		}
		if (spawnLocation == 3)
		{
			_munchiePosition->X = rand() % 340;
			_munchiePosition->Y = rand() % 1024 + 510;
		}
		if (spawnLocation == 4)
		{
			_munchiePosition->X = rand() % 768 + 680;
			_munchiePosition->Y = rand() % 1024 + 510;
		}
		_random = !_random;
	}
}

void Munchie::Draw(int elapsedTime)
{
	SpriteBatch::Draw(_munchieTexture, _munchiePosition, _munchieRect, Vector2::Zero, 1.0f, 0.0f, Color::White, SpriteEffect::NONE); //Draws Munchie
}

void Munchie::UpdateMunchie(int elapsedTime)
{
	_munchieCurrentFrameTime += elapsedTime;
	if (_munchieCurrentFrameTime > _cMunchieFrameTime)
	{
		_munchieFrameCount++;
		if (_munchieFrameCount >= 2)
			_munchieFrameCount = 0;
		_munchieCurrentFrameTime = 0;
	}
	_munchieRect->X = _munchieRect->Width * _munchieFrameCount;
	_munchieRect->Y = _munchieRect->Height;
}

void Munchie::CheckRandom(Input::KeyboardState* keyboardState)
{
	if (keyboardState->IsKeyDown(_rButton) && !_rKeyDown)
	{
		_rKeyDown = true;
		_random = !_random;
	}
	if (keyboardState->IsKeyUp(_rButton))
	{
		_rKeyDown = false;
	}
}
