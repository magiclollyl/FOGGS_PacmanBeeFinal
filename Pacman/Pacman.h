#pragma once

// If Windows and not in Debug, this will run without a console window
// You can use this to output information when debugging using cout or cerr
#ifdef WIN32 
	#ifndef _DEBUG
		#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
	#endif
#endif

// Just need to include main header file
#include "S2D/S2D.h"

// Reduces the amount of typing by including all classes in S2D namespace
using namespace S2D;

class Ghost;


// Declares the Pacman class which inherits from the Game class.
// This allows us to overload the Game class methods to help us
// load content, draw and update our game.
class Pacman
{
private:
	// Data to represent Pacman
	Rect* _pacmanSourceRect;
	Texture2D* _pacmanTexture;
	Input::Keys _up;
	Input::Keys _down;
	Input::Keys _left;
	Input::Keys _right;
	Input::Keys _leftShift;

	//Constant data for Game Variables 
	const float _cPacmanSpeed;
	const int _cPacmanFrameTime;

	int _direction = 0;

	int _pacmanFrame;
	int _pacmanCurrentFrameTime;

	void Input(int elapsedTime, Input::KeyboardState* state);
	void CheckViewportCollision();

public:
	/// <summary> Constructs the Pacman class. </summary>
	Pacman(Input::Keys up, Input::Keys down, Input::Keys left, Input::Keys right, Input::Keys leftShift);

	/// <summary> Destroys any data associated with Pacman class. </summary>
	virtual ~Pacman();

	/// <summary> All content should be loaded in this method. </summary>
	void virtual LoadPacmanContent();

	/// <summary> Called every frame - update game logic here. </summary>
	void virtual Update(int elapsedTime, Input::KeyboardState* state);

	/// <summary> Called every frame - draw game here. </summary>
	void virtual Draw(int elapsedTime);

	Vector2* _pacmanPosition;
	bool dead;
	float _pacmanSpeedMultiplier;
	float _pacmanSpeed;
	float _cherryMult;
	float _levelHandicap;
};