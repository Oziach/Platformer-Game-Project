#include "Door.h"
static KMTexture spritesheet;
static std::vector<SDL_Rect> clips;

Door::Door(int x, int y, int rot, int fl, int* room, int* noOfPads) {
	xPos = x;
	yPos = y;
	width = 12;
	height = 16;
	rotation = rot;
	this->room = room;

	//flip
	if (fl == 1) { flip = SDL_FLIP_HORIZONTAL; }
	else if (fl == 2) { flip = SDL_FLIP_VERTICAL; }

	hitbox.x = xPos + 3; hitbox.y = yPos + 6; hitbox.w = width - 6; hitbox.h = height - 6;
	padsLeft = noOfPads;

	setSpriteStuff();
}

void Door::setSpriteStuff() {

	spritesheet.loadFromImage("sprites//DOOR.png");
	loadClips(clips, 16);

	s_spritesheet = &spritesheet;
	s_clips = &clips;

	framesBetweenLoops = 72;
	framesPerClip = 6;
	calculateFramesPerLoop();


}

void Door::handleCollision(KMPlayerCharacter& husk) {

	if (*padsLeft == 0) { locked = false; }
	else { locked = true; }

	if (CHandler::checkCollision(husk.getCollider(), hitbox)) {
		if (!locked) {
			(*room)++;
			
		    husk.respawn();
		}
	}
}

void Door::render(SDL_Rect camera, int minClip , int maxClip ) {
	if (!locked) {
		spritesheet.render(xPos - camera.x, yPos - camera.y, &clips[0]);
	}
	else {
		spritesheet.render(xPos - camera.x, yPos - camera.y, &clips[15]);
	}
}

