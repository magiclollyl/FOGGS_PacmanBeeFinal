#pragma once
#include "S2D/S2D.h"

using namespace S2D;

class Fountain
{
private:
	Texture2D* _fountainTexture;
	Rect* _fountainRect;

	const int _cFountainFrameTime;

	int _fountainFrameCount;
	int _fountainCurrentFrameTime;

public:
	Fountain();
	~Fountain();
	Vector2* _fountainPosition;
	void LoadFountainContent();
	void DrawFountain(int elapsedTime);
	void UpdateFountain(int elapsedTime);
};

