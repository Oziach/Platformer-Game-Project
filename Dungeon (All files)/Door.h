#pragma once
#include "KMGameObject.h"
class Door : public KMGameObject {

private:
	int* room;
	int* padsLeft = NULL;
	bool locked;
public:
	Door(int x, int y, int rot, int fl, int* room, int* noOfPads );
	void setSpriteStuff();
	void handleCollision(KMPlayerCharacter& husk);
	void render(SDL_Rect camera, int minClip = 0, int maxClip = 0);
};

