#include "Carnivore.h"
const float GRAVITY = 400;


static KMTexture spritesheet;
static std::vector<SDL_Rect> clips;

Carnivore::Carnivore(int x, int y, int rot, int fl) {


	xPos = x; 
	yPos = y; originalYPos = yPos; instancedYPos = float(yPos);

	rotation = rot;

	width = 7; height = 11;

	if (rotation == 0) { shiftCollider(); }

	triggerBox = { xPos - 20, yPos - 20, width + 40, height + 20 };

	//flip
	if (fl == 1) { flip = SDL_FLIP_HORIZONTAL; }
	else if (fl == 2) { flip = SDL_FLIP_VERTICAL; }


	setSpriteStuff();

}

void Carnivore::setSpriteStuff() {

	spritesheet.loadFromImage("sprites/bw/CARNIVORE.png");

	loadClips(clips, 5);
	setActiveClip(3);
	s_spritesheet = &spritesheet;
	s_clips = &clips;

	framesBetweenLoops = 0;
	framesPerClip = 10;
	calculateFramesPerLoop();
}


//movement
void Carnivore::move(KMPlayerCharacter& husk, float timeStep) {


	if (isActive()) { moveActive(timeStep); }

	yVel += GRAVITY * timeStep;
	instancedYPos += yVel * timeStep;
	yPos = int(instancedYPos);

	if (yPos > originalYPos) { yPos = originalYPos; instancedYPos = originalYPos; yVel = 0; }

	shiftCollider();
}


void Carnivore::moveActive(float timeStep) {

	if (activeTimer >= 1.f) {
		if (yPos == originalYPos) {
			yVel = -JUMP_VEL;
			activeTimer = 0;
		}
	}	
}

void Carnivore::handleTrigger(KMPlayerCharacter& husk, float timeStep) {
	if (CHandler::checkCollision(husk.getCollider(), triggerBox)) {
		active = true;
		if (activeTimer == -1.f) { activeTimer = 1.f; }
		else { activeTimer += timeStep; }
	}
	else {
		active = false;
		activeTimer = -1.f;
	}
}


//rendering
void Carnivore::renderPassive(SDL_Rect camera) {
	render(camera, 0, 3);
}

void Carnivore::renderActive(SDL_Rect camera) {
	render(camera, 3, 4);
}

void Carnivore::renderNPC(SDL_Rect camera) {
	if (isActive()) { renderActive(camera); }
	else { renderPassive(camera); }
}

void Carnivore::shiftCollider() {
	hitbox.x = xPos + 1; hitbox.y = yPos + 1; hitbox.w = width - 2; hitbox.h = height - 1;
}