#include "S2D/S2D.h"

using namespace S2D;

class Cherry
{
private:
	int _cherryFrameCount;
	int _cherryCurrentFrameTime;
	int _randomTimer;

	Rect* _cherryRect;
	Texture2D* _cherryTexture;


	const int _cCherryFrameTime;
	

public:
	Vector2* _cherryPosition;

	Cherry();
	~Cherry();
	void LoadCherryContent();
	void Update(int elapsedTime);
	void Draw(int elapsedTime);
	void Randomise();

};
