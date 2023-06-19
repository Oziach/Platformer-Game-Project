#pragma once
#include<SDL.h>
#include"Tile.h"
#include<vector>
#include<fstream>
#include<sstream>

//#include"CHandler.h"
#include"Tile.h"
#include"KMTexture.h"
#include"KMPlayerCharacter.h"

class KMTiler {
private:

	std::vector < std::vector<Tile> > tiles;
	std::vector <SDL_Rect> tileRects;
	std::vector<SDL_Rect> clipsVector;
	KMTexture tilesetTexture;

	 int roomType;
	 int highestSolidTile = 23;

	 int levelWidth = 0;
	 int levelHeight = 0;

public:
	static const int TILE_WIDTH = 16;
	static const int TILE_HEIGHT = 16;
	static const int TILE_DIMENSION = 16;
	

public:
	KMTiler();

	//sets the room type. To be called immediately after room is incremented in main
	bool loadTilesetTexture(int room);
	void loadTileClips(int TILESET_WIDTH, int TILESET_HEIGHT, int NO_OF_CLIPS, int room);



	//loads tile locations from map file into array
	bool loadTiles(KMPlayerCharacter& husk, int room);
	void loadTileRects(std::string path);
	void loadTileRects(int room);

	//load bigRects into given vector
	void loadBigRects(std::vector<SDL_Rect>& rectVector, std::string path);
	//load big rects with respect to room
	void loadBigRects(std::vector<SDL_Rect>& rectVector, int room);


	//renders tiles on screen
	void renderTiles(SDL_Rect camera);

	//getters
	std::vector<SDL_Rect>& getTileRects();
	int getHighestSolidTile();
	int getLevelWidth();
	int getLevelHeight();
};

