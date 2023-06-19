#pragma once

#include<SDL.h>
#include"KMGameObject.h"
#include"KMTexture.h"
#include"CHandler.h"

class Spike : public KMGameObject
{
private:
	int variant = 0;

public:
	Spike(int x, int y, int rot, int fl, int var);
	void setSpriteStuff();
	//void render(SDL_Rect camera, int minClip = 0, int maxClip = 0);
};

