#include "Spikes.h"

static KMTexture spritesheet;
static std::vector<SDL_Rect> clips;

Spikes::Spikes(int x, int y, int rot, int fl) {


	xPos = x;
	yPos = y;

	rotation = rot;

	width = 4; height = 4; 
	
	if (rotation == 0) {
		hitbox.x = xPos; hitbox.y = yPos + 1; hitbox.w = width; hitbox.h = height - 1;
	}
	else if (rotation == 90 || rotation == 270) {
		hitbox.x = xPos + 1; hitbox.y = yPos; hitbox.w = width - 2; hitbox.h = height;
	}


	//flip
	if (fl == 1) { flip = SDL_FLIP_HORIZONTAL; }
	else if (fl == 2) { flip = SDL_FLIP_VERTICAL; }

	setSpriteStuff();

}

void Spikes::setSpriteStuff() {

	spritesheet.loadFromImage("sprites/pw/SPIKES.png");
	loadClips(clips, 2);

	s_spritesheet = &spritesheet;
	s_clips = &clips;

	framesBetweenLoops = 0;
	framesPerClip = 15;
	calculateFramesPerLoop();
}
