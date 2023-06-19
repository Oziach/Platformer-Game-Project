#include "Spike.h"

static KMTexture spritesheetVar0;
static KMTexture spritesheetVar1;
static KMTexture spritesheetVar2;
static std::vector<SDL_Rect> clipsVar0;
static std::vector<SDL_Rect> clipsVar1;
static std::vector<SDL_Rect> clipsVar2;


Spike::Spike(int x, int y, int rot, int fl, int var) {

	
	xPos = x;
	yPos = y;

	rotation = rot;
	variant = var;


	switch (variant) {
	case 0: width = 7; height = 11; hitbox.x = xPos + 1; hitbox.y = yPos + 3; hitbox.w = width - 2; hitbox.h = height - 3; break;
	case 1: width = 11; height = 7; hitbox.w = width - 2; hitbox.h = height - 2; hitbox.x = xPos; hitbox.y = yPos + 1; break;
	case 2: width = 7; height = 10; hitbox.x = xPos + 1; hitbox.w = width - 2; hitbox.h = height - 3; hitbox.y = yPos; break;
	}


	//flip
	if (fl == 1) { flip = SDL_FLIP_HORIZONTAL; }
	else if (fl == 2) { flip = SDL_FLIP_VERTICAL; }

	setSpriteStuff();
	
}

void Spike::setSpriteStuff() {
	switch (variant) {
	case 0: if (!spritesheetVar0.isTextureLoaded()) { spritesheetVar0.loadFromImage("sprites/rw/SPIKE_FLOOR.png"); break; }
	case 1: if (!spritesheetVar1.isTextureLoaded()) { spritesheetVar1.loadFromImage("sprites/rw/SPIKE_WALL.png"); break; }
	case 2: if (!spritesheetVar2.isTextureLoaded()) { spritesheetVar2.loadFromImage("sprites/rw/SPIKE_ROOF.png"); break; }
	}

	switch (variant) {
	case 0: if (!(clipsVar0.size() > 0)) { loadClips(clipsVar0, 8); }; break;
	case 1: if (!(clipsVar1.size() > 0)) { loadClips(clipsVar1, 8); }; break;
	case 2: if (!(clipsVar2.size() > 0)) { loadClips(clipsVar2, 8); }; break;
	}

	switch (variant) {
	case 0:	s_spritesheet = &spritesheetVar0; s_clips = &clipsVar0; break;
	case 1:	s_spritesheet = &spritesheetVar1; s_clips = &clipsVar1; break;
	case 2:	s_spritesheet = &spritesheetVar2; s_clips = &clipsVar2; break;
	}

	framesBetweenLoops = 72;
	framesPerClip = 4;
	calculateFramesPerLoop();

}

