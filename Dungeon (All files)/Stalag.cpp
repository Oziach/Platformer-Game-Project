#include "Stalag.h"

static KMTexture spritesheet;
static std::vector<SDL_Rect> clips;

Stalag::Stalag(int x, int y, int rot, int fl) {


	xPos = x;
	yPos = y;
		
	rotation = rot;

	width = 8; height = 10;

	hitbox.x = xPos + 1; hitbox.y = yPos; hitbox.w = width - 2; hitbox.h = height - 1;
	

	//flip
	if (fl == 1) { flip = SDL_FLIP_HORIZONTAL; }
	else if (fl == 2) { flip = SDL_FLIP_VERTICAL; }


	setSpriteStuff();

	if (rotation == 90) {
		width = 10; height = 8;
		hitbox.x = xPos + 1; hitbox.y = yPos + 1; hitbox.w = width - 2; hitbox.h = height - 2;
	}
}

void Stalag::setSpriteStuff() {

	spritesheet.loadFromImage("sprites/bw/STALAG.png");
	loadClips(clips, 6);

	s_spritesheet = &spritesheet;
	s_clips = &clips;

	framesBetweenLoops = 72;
	framesPerClip = 4;
	calculateFramesPerLoop();

}

