#pragma once
#include<SDL.h>
#include"KMPlayerCharacter.h"

class KMPlayerCharacter;


class CHandler {
public:

	////collision constants
	/*const int NO_COLLISION = 0;
	const int TOP_COLLISION = 1;
	const int BOTTOM_COLLISION = 2;
	const int LEFT_COLLISION = 3;
	const int RIGHT_COLLISION = 4;*/

	enum CollisionDirection {
		NO_COLLISION = 0,
		TOP_COLLISION = 1,
		BOTTOM_COLLISION = 2,
		LEFT_COLLISION = 3,
		RIGHT_COLLISION = 4
	};



	static bool checkCollision(SDL_Rect& a, SDL_Rect& b);
	static CollisionDirection getCollisionDirection(KMPlayerCharacter& husk, SDL_Rect&b, float timeStep);
};

