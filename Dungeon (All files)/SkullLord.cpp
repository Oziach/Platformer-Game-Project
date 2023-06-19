#include "SkullLord.h"

static KMTexture spritesheet;
static std::vector<SDL_Rect> clips;

SkullLord::SkullLord(int x, int y, int rot, int fl, SDL_Rect wanderRect) {


	xPos = x; instancedXPos = float(xPos);
	yPos = y; 
	rotation = rot;

	width = 32; height = 16;
	hitbox.w = width - 4; hitbox.h = height - 4;
	shiftCollider();

	triggerBox = wanderRect;
	wanderBox = wanderRect;

	//flip
	if (fl == 1) { flip = SDL_FLIP_HORIZONTAL; }
	else if (fl == 2) { flip = SDL_FLIP_VERTICAL; }


	setSpriteStuff();

}

void SkullLord::setSpriteStuff() {

	spritesheet.loadFromImage("sprites/rw/SKULL_LORD.png");

	loadClips(clips, 4);
	setActiveClip(2);

	s_spritesheet = &spritesheet;
	s_clips = &clips;

	framesBetweenLoops = 0;
	framesPerClip = 12;
	calculateFramesPerLoop();
}

void SkullLord::move(KMPlayerCharacter& husk, float timeStep) {

	int directionX = int(husk.getXPos()) - int(xPos);
	if (directionX != 0) {
		directionX /= abs(directionX); //gives +1 if need to move to right, -1 if left
	}

	//if not aggro
	if (!active) {		
		if (xVel != PASSIVE_XVEL && xVel != -PASSIVE_XVEL) { 
			int direction; if (facingRight) { direction = 1; }	else { direction = -1; }
			xVel = PASSIVE_XVEL * direction; }
	}
	else { //if aggro

		xVel = ACTIVE_XVEL * directionX;

		//if NPCxVel not in direction of player after aggroing, set in in player's direction
		if (directionX != 0) { xVel = abs(xVel) * directionX; }

	}

	instancedXPos += xVel * timeStep;
	xPos = int(instancedXPos);
	shiftCollider();

	if (xPos < wanderBox.x) { xPos = wanderBox.x; xVel = -xVel; }
    else if (xPos + width > wanderBox.x + wanderBox.w) { xPos = wanderBox.x + wanderBox.w - width; xVel = -xVel; }
	shiftCollider();

	//facingRight
	if (xVel > 0) { facingRight = true; }
	else if (xVel < 0) { facingRight = false; }

}



//rendering
void SkullLord::renderPassive(SDL_Rect camera) {
	render(camera, 0, 1);
}

void SkullLord::renderActive(SDL_Rect camera) {
	render(camera, 2, 3);
}

void SkullLord::renderNPC(SDL_Rect camera) {
	flip = facingRight ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

	if (active) { renderActive(camera); }
	else { renderPassive(camera); }
}

void SkullLord::shiftCollider() {

	hitbox.x = xPos + 4; hitbox.y = yPos + 2;
}