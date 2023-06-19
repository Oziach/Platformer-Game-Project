#pragma once
#include "KMNPC.h"
class Carnivore :  public KMNPC {

private:

	const int JUMP_VEL = 90;

	int originalYPos;
	float instancedYPos;

	float yVel = 0;

	float activeTimer = -1.f;

public:

	Carnivore(int x, int y, int rot, int fl);
	void setSpriteStuff();

	void move(KMPlayerCharacter& husk, float timeStep);
	void moveActive(float timeStep);

	void handleTrigger(KMPlayerCharacter& husk, float timeStep);

	void renderNPC(SDL_Rect camera);
	void renderPassive(SDL_Rect camera);
	void renderActive(SDL_Rect camera);

	void shiftCollider();
};

