#pragma once

#include<SDL.h>
#include<vector>
#include"KMTexture.h"
#include"KMPlayerCharacter.h"
#include"CHandler.h"

class KMGameObject {

protected:
	int xPos = 0;
	int yPos = 0;
	int rotation = 0;
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	int width = 0;
	int height = 0;

	SDL_Rect hitbox = { 0,0,0,0 };

	KMTexture* s_spritesheet = NULL;
	std::vector <SDL_Rect>* s_clips = NULL;
	

	//animation
	int frame = 0;
	int framesBetweenLoops = 0;
	int framesPerClip = 0;
	int framesPerLoop = 0;


public:

	virtual void render(SDL_Rect camera, int minClip = 0, int maxClip = 0);
	virtual void handleCollision(KMPlayerCharacter& husk);

	void loadClips(std::vector<SDL_Rect>& clips, int noOfClips);
	void calculateFramesPerLoop();

	//getters
	SDL_Rect getAnimRect();
};

