#pragma once
#include<SDL.h>
#include"KMGameObject.h"
#include"CHandler.h"

class LavaPool : public KMGameObject {

private:
	int variant = 0;

public:
	LavaPool(int x, int y, int rot, int fl, int var);
	void setSpriteStuff();

	void handleCollision(KMPlayerCharacter& husk, float timeStep);
};

