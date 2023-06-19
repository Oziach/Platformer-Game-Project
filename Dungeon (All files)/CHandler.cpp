#include "CHandler.h"
#include<cmath>

class KMPlayerCharacter;


 bool CHandler :: checkCollision(SDL_Rect& a, SDL_Rect& b) {

	//sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;


	//the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w - 1;
	topA = a.y;
	bottomA = a.y + a.h - 1;


	//the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w - 1;
	topB = b.y;
	bottomB = b.y + b.h - 1;



	//if no collison
	if (bottomA < topB) {
		return false;
	}

	if (topA > bottomB) {
		return false;
	}

	if (rightA < leftB) {
		return false;
	}

	if (leftA > rightB) {
		return false;
	}

	//If collsion
	return true;

}


 


//returns direction of collision 
//this function is to be called ONLY AFTER COLLISION BETWEEN RECTS TAKES PLACE
 
 
CHandler::CollisionDirection CHandler :: getCollisionDirection(KMPlayerCharacter& husk, SDL_Rect& b, float timeStep) {
//
//std::cout << " tile: " << b.x << "   " << b.y << "    " << b.w << "   " << b.h << "    \n";
	float xVel = (husk.getRawXVel());
	float yVel = (husk.getYVel()) * timeStep;

	int xPos = husk.getCollider().x;
	int yPos = husk.getCollider().y;
	int charWidth = husk.getCollider().w;
	int charHeight = husk.getCollider().h;

	int boxCornerX;
	int boxCornerY;

	int cornerX;
	int cornerY;


//determine which corner of the box is being dealt with
	if (xVel > 0) {
		if (yVel >= 0) {

			//box top left
			boxCornerX = b.x;
			boxCornerY = b.y;

			cornerX = xPos + charWidth - 1;
			cornerY = yPos + charHeight - 1;
		}
		else if (yVel < 0) {

			//box bottom left
			boxCornerX = b.x;
			boxCornerY = b.y + b.h - 1;

			cornerX = xPos + charWidth;
			cornerY = yPos;
		}
	}
	//if xVel < 0
	else {
		if (yVel >= 0) {

			//box top right
			boxCornerX = b.x + b.w - 1;
			boxCornerY = b.y;

			cornerX = xPos;
			cornerY = yPos + charHeight - 1;


		}
		else if (yVel < 0)
		{
			//box bottom right

			boxCornerX = b.x + b.w - 1;
			boxCornerY = b.y + b.h - 1;

			cornerX = xPos;
			cornerY = yPos;

		}
	}


//	//determine inclinations
	float huskInclination = abs(float((yVel / xVel)));
	float cornerInclination = abs(float((cornerY - boxCornerY)) / float((cornerX - boxCornerX)));


	//determine vertical or horizontal
	bool verticalSide = huskInclination < cornerInclination;
	bool gVerticalSide = true;


	//determine side

	//if bumping against vertical side
	if (verticalSide) {
		if (xVel > 0) {
			return LEFT_COLLISION;
		}
		else if (xVel < 0) {
			return RIGHT_COLLISION;
		}
	}

	//if bumping against horizontal side
	else {
		if (yVel > 0) {
			return TOP_COLLISION;
		}
		else if (yVel <= 0) {
			return BOTTOM_COLLISION;
		}
	}

	return NO_COLLISION;
}
