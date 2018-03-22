#include "S2D/S2D.h"

using namespace S2D;

class Ghost
{
private:	
	Rect* _ghostSourceRect;
	Texture2D* _ghostTexture;
	int _ghostDirection;
	int _xORy;
	int _colour;
	Vector2* _ghostFollowDirection;
	Vector2* whereIsPacman;

	int _ghostFrameCount;
	int _ghostCurrentFrameTime;
	const int _cGhostFrameTime;

public:
	Rect* _ghostPosRect;
	Ghost();
	float _ghostSpeed;

	virtual ~Ghost();

	void virtual LoadGhostContent();

	void virtual Draw(int elapsedTime);

	void UpdateGhosts(int elapsedTime, Vector2* pacmanPosition);

};

