#include "Pad.h"

static KMTexture spritesheet;
static std::vector<SDL_Rect> clips;

Pad::Pad(int x, int y, int rot, int fl, int pressedFrames, int* noOfPads) {


	xPos = x;
	yPos = y;

	rotation = rot;

	width = 10; height = 2;

	maxFrames = pressedFrames;
	padsLeft = noOfPads;

	//flip
	if (fl == 1) { flip = SDL_FLIP_HORIZONTAL; }
	else if (fl == 2) { flip = SDL_FLIP_VERTICAL; }

	setSpriteStuff();

	if (rotation == 90) { width = 2; height = 10; }
	hitbox.x = xPos; hitbox.y = yPos; hitbox.w = width; hitbox.h = height;
}


void Pad::setSpriteStuff() {

	spritesheet.loadFromImage("sprites/PAD.png");
	loadClips(clips, 2);

	s_spritesheet = &spritesheet;
	s_clips = &clips;
}

void Pad::handleCollision(KMPlayerCharacter& husk) {
	
	if (CHandler::checkCollision(husk.getCollider(), hitbox)) {
		if (pressed == false) {
			(*padsLeft) -= 1;
			pressed = true;
			
		}		
		countdown = maxFrames;
	}

	if (countdown > 0) {
		countdown--;
	}

	if (countdown == 0) {
		pressed = false;
		(*padsLeft) += 1;
		countdown = -1;
	}

}

void Pad::render(SDL_Rect camera, int minClip, int maxClip) {
	if (pressed) {
		spritesheet.render(xPos - camera.x, yPos - camera.y, &clips[1], rotation);
	}
	else { //if not pressed
		spritesheet.render(xPos - camera.x, yPos - camera.y, &clips[0], rotation);
	}
}


bool Pad::isPressed() { return pressed; }