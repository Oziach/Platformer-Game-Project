#pragma once

#include<SDL.h>
#include<iostream>

//a SDL_Renderer kmRenderer MUST be defined elsewhere for a particular window in order for this class to work; ONLY for that window
extern SDL_Renderer* kmRenderer;

class KMTexture {

private:	
	SDL_Texture* kmTexture;

	int TEXTURE_WIDTH;
	int TEXTURE_HEIGHT;

public:
	KMTexture();
	~KMTexture();
	void free();

	bool loadFromImage(std::string path);

	void setAlpha(int a);
	void render(int x, int y, SDL_Rect* clip = NULL, int rotation = 0, SDL_Point* centre = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	int getTextureWidth();
	int getTextureHeight();
	bool isTextureLoaded();

};
