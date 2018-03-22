#include "Fountain.h"


void Fountain::LoadFountainContent()
{
	_fountainTexture = new Texture2D();
	_fountainTexture->Load("Textures/WaterFountain.png", true);
	_fountainPosition = new Vector2(440.0f, 330.0f);
	_fountainRect = new Rect(0.0f, 0.0f, 130, 125);
}

Fountain::Fountain() : _cFountainFrameTime(750)
{
	_fountainFrameCount = 0;
	_fountainCurrentFrameTime = 0;
	LoadFountainContent();
}


Fountain::~Fountain()
{
	delete _fountainTexture;
	delete _fountainRect;
	delete _fountainPosition;
}

void Fountain::UpdateFountain(int elapsedTime)
{
	_fountainCurrentFrameTime += elapsedTime;
	if (_fountainCurrentFrameTime > _cFountainFrameTime)
	{
		_fountainFrameCount++;
		if (_fountainFrameCount >= 2)
			_fountainFrameCount = 0;
		_fountainCurrentFrameTime = 0;
	}
	_fountainRect->X = _fountainRect->Width * _fountainFrameCount;
	_fountainRect->Y = _fountainRect->Height;
}

void Fountain::DrawFountain(int elapsedTime)
{
	SpriteBatch::Draw(_fountainTexture, _fountainPosition, _fountainRect, Vector2::Zero, 1.0f, 0.0f, Color::White, SpriteEffect::NONE);
}