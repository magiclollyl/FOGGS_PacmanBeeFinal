#include "Cherry.h"
#include "Controller.h"

void Cherry::LoadCherryContent()
{
	_cherryTexture = new Texture2D();
	_cherryTexture->Load("Textures/cherryFlower.png", true);
	_cherryRect = new Rect(0.0f, 0.0f, 32, 32);
	_cherryPosition = new Vector2(rand() % Graphics::GetViewportWidth(),rand() % Graphics::GetViewportHeight());
}


Cherry::~Cherry()
{
	delete _cherryRect;
	delete _cherryTexture;
	delete _cherryPosition;
}

Cherry::Cherry() : _cCherryFrameTime(750)
{
	_cherryFrameCount = 0;
	_cherryCurrentFrameTime = 0;
	_randomTimer = 0;
	LoadCherryContent();
}

void Cherry::Update(int elapsedTime)
{
	_cherryCurrentFrameTime += elapsedTime;
	if (_cherryCurrentFrameTime > _cCherryFrameTime)
	{
		_cherryFrameCount++;
		if (_cherryFrameCount >= 2)
			_cherryFrameCount = 0;
		_cherryCurrentFrameTime = 0;
	}
	_cherryRect->X = _cherryRect->Width * _cherryFrameCount;
	_cherryRect->Y = _cherryRect->Height;
	Randomise();
}

void Cherry::Draw(int elapsedTime)
{
	SpriteBatch::Draw(_cherryTexture, _cherryPosition, _cherryRect, Vector2::Zero, 1.0f, 0.0f, Color::White, SpriteEffect::NONE);
}

void Cherry::Randomise()
{
	if (_randomTimer == 150)
	{
		_cherryPosition->X = rand() % (Graphics::GetViewportWidth() - 10);
		_cherryPosition->Y = rand() % (Graphics::GetViewportHeight() - 10);
		_randomTimer = 0;
	}
	else
	{
		_randomTimer += 1;
	}
}