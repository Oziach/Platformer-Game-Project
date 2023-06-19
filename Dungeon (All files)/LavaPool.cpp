#include "LavaPool.h"

static KMTexture spritesheetVar0;
static KMTexture spritesheetVar1;
static KMTexture spritesheetVar2;
static KMTexture spritesheetVar3;
static KMTexture spritesheetVar4;
static std::vector<SDL_Rect> clips;

LavaPool::LavaPool(int x, int y, int rot, int fl, int var) {
	xPos = x;
	yPos = y;
	width = 16;
	height = 16;
	rotation = rot;
	variant = var;

	//flip
	if (fl == 1) { flip = SDL_FLIP_HORIZONTAL; }
	else if (fl == 2) { flip = SDL_FLIP_VERTICAL; }

	hitbox.x = xPos; hitbox.y = yPos + 3; hitbox.w = width; hitbox.h = height - 3;

	setSpriteStuff();
}

void LavaPool::setSpriteStuff() {
	if (!spritesheetVar0.isTextureLoaded()) { spritesheetVar0.loadFromImage("sprites/rw/LAVA_EDGE.png"); }
	if (!spritesheetVar1.isTextureLoaded()) { spritesheetVar1.loadFromImage("sprites/rw/LAVA_MIDDLE.png"); }
	if (!spritesheetVar2.isTextureLoaded()) { spritesheetVar2.loadFromImage("sprites/rw/LAVA_EDGE2.png"); }
	if (!spritesheetVar3.isTextureLoaded()) { spritesheetVar3.loadFromImage("sprites/rw/LAVA_MIDDLE2.png"); }
	if (!spritesheetVar4.isTextureLoaded()) { spritesheetVar4.loadFromImage("sprites/rw/LAVA_ALONE.png"); }

	switch (variant) {
	case 0:	s_spritesheet = &spritesheetVar0; break;
	case 1:	s_spritesheet = &spritesheetVar1; break;
	case 2:	s_spritesheet = &spritesheetVar2; break;
	case 3:	s_spritesheet = &spritesheetVar3; break;
	case 4:	s_spritesheet = &spritesheetVar4; break;
	}

	loadClips(clips, 3);
	s_clips = &clips;

	framesPerClip = 12;
	framesBetweenLoops = 0;
	framesPerLoop = (framesPerClip * s_clips->size()) + framesBetweenLoops;

}

void LavaPool::handleCollision(KMPlayerCharacter& husk, float timeStep) {
	
	if (CHandler::checkCollision(husk.getCollider(), hitbox)) { //if collision

		CHandler::CollisionDirection direction = CHandler::getCollisionDirection(husk, hitbox, timeStep);


		if (direction == CHandler::LEFT_COLLISION) {
			husk.setXPos(float(hitbox.x - hitbox.w));
			husk.shiftCollider();

		}
		else if (direction == CHandler::RIGHT_COLLISION) {
			husk.setXPos(float(hitbox.x + hitbox.w));
			husk.shiftCollider();
		}


		if (direction == CHandler::BOTTOM_COLLISION) {
			husk.setYPos(float(hitbox.y + hitbox.h));
			husk.setYVel(0);
			husk.shiftCollider();
		}

		else if (direction == CHandler::TOP_COLLISION) { husk.handleDeath(); }

	

	}
}