#include "S2D/S2D.h"

using namespace S2D;

class Munchie
{
private:
	// Data to represent Munchie
	int _munchieFrameCount;
	Rect* _munchieRect;
	Texture2D* _munchieTexture;
	bool _rKeyDown;
	int spawnLocation;

	Input::Keys _rButton;

	//Constant data for Game Variables 
	const int _cMunchieFrameTime;

	int _munchieCurrentFrameTime;

	void UpdateMunchie(int elapsedTime);
	void CheckRandom(Input::KeyboardState* state);

public:
	bool _random;
	Vector2* _munchiePosition;
	/// <summary> Constructs the Munchie class. </summary>
	Munchie(Input::Keys rButton);

	/// <summary> Destroys any data associated with Munchie class. </summary>
	virtual ~Munchie();

	/// <summary> All content should be loaded in this method. </summary>
	void LoadMunchieContent();

	/// <summary> Called every frame - update game logic here. </summary>
	void Update(int elapsedTime, Input::KeyboardState* keyboardState);

	/// <summary> Called every frame - draw game here. </summary>
	void Draw(int elapsedTime);
};