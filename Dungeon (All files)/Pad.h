#pragma once
#include "KMGameObject.h"
class Pad : public KMGameObject {

private:
	int* padsLeft = NULL;
	bool pressed = false;
	int countdown = -1;
	int maxFrames = 300;

public:
	Pad(int x, int y, int rot, int fl, int pressedFrames, int* noOfPads);
	void setSpriteStuff();
	void handleCollision(KMPlayerCharacter& husk);
	void render(SDL_Rect camera, int minClip = 0, int maxClip = 0);
	bool isPressed();
};

