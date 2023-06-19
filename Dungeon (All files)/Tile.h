#pragma once
#include<SDL.h>
#include"KMTexture.h"
#include<vector>

class Tile {
private:

	SDL_Rect tileRect;
	int tileType;
	bool solid;

public:
	const int TILE_WIDTH = 16;
	const int TILE_HEIGHT = 16;
	const int TILE_DIMENSION = 16;

	Tile(int x, int y, int tType);

	//void render(KMTexture* tilesetTexture, SDL_Rect tileClips[], SDL_Rect camera);
	void render(KMTexture* tilesetTexture, std::vector<SDL_Rect>* tileClips, SDL_Rect camera);

	//getters
	int getType();
	SDL_Rect& getTileRect();

	int getX();
	int getY();
	
	//getters AND setters
	bool isSolid();
	void isSolid(bool solid);
};

