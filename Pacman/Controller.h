#include "S2D/S2D.h"

#define MUNCHIECOUNT 50
#define GHOSTCOUNT 2

using namespace S2D;
class Munchie;
class Pacman;
class Ghost;
class Cherry;
class Fountain;

class Controller : public Game
{
private:
	// Position for String
	Vector2* _stringPosition;

	// Data for Menu 
	Texture2D* _menuBackground;
	Rect* _menuRectangle;
	Vector2* _menuStringPosition;
	bool _start;
	bool _paused;
	bool _pKeyDown;
	Texture2D* _mainBackground;
	int waitTime;
	int _playerScore;
	int _playerLevel;

	bool _gameOver;
	bool _gameWon;

	void CheckPaused(Input::KeyboardState* state, Input::Keys pauseKey);

	Munchie* _munchie[MUNCHIECOUNT];
	Pacman* _pacman;
	Ghost* _ghosts[GHOSTCOUNT];
	Cherry* _cherry;
	Fountain* _fountain;

	SoundEffect* _pop;
	SoundEffect* _birds;
	SoundEffect* _levelUp;
	SoundEffect* _cherryGet;
	SoundEffect* _gameWin;
	SoundEffect* _splash;

public:
	/// <summary> Constructs the Controller class. </summary>
	Controller(int argc, char* argv[]);

	/// <summary> Destroys any data associated with Controller class. </summary>
	virtual ~Controller();

	/// <summary> All content should be loaded in this method. </summary>
	void virtual LoadContent();

	/// <summary> Called every frame - update game logic here. </summary>
	void virtual Update(int elapsedTime);

	/// <summary> Called every frame - draw game here. </summary>
	void virtual Draw(int elapsedTime);

	void Input(int elapsedTime, Input::MouseState* mouseState);
	void DeadPacman();
	void EatMunchie();
	void EatCherry();
	void WetBee();

	void WaitTime();
	void Restart(Input::KeyboardState* state);
	void LevelUp();

	bool CollisionCheck(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2);
};