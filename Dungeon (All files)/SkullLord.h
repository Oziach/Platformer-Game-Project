#pragma once
#include"KMNPC.h"

class SkullLord : public KMNPC {

	const float PASSIVE_XVEL = 42;
	const float ACTIVE_XVEL = 70;

	float instancedXPos;
	float xVel = PASSIVE_XVEL;;

	bool facingRight = true;
	SDL_Rect wanderBox = { 0,0,0,0 };


public:
	SkullLord(int x, int y, int rot, int fl, SDL_Rect wanderRect);
	void setSpriteStuff();

	void move(KMPlayerCharacter& husk, float timeStep);



	void renderNPC(SDL_Rect camera);
	void renderPassive(SDL_Rect camera);
	void renderActive(SDL_Rect camera);

	void shiftCollider();
};

