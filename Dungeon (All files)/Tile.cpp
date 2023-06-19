
#include "Tile.h"

Tile::Tile(int x, int y, int tType) {
	tileRect.x = x;
	tileRect.y = y;

	tileRect.w = TILE_WIDTH;
	tileRect.h = TILE_HEIGHT;

	tileType = tType;
	
}

//render tile relative to camera, BUT NOT NECESARILY WITHIN THE CAMERA. The function that calls this needs to handle the camera collision with tile
void Tile:: render(KMTexture* tilesetTexture, std::vector<SDL_Rect>* tileClips, SDL_Rect camera) {

	if (tileType > -1) {
		tilesetTexture->render(tileRect.x - camera.x, tileRect.y - camera.y, &tileClips->at(tileType));
	}

}

//getters

int Tile::getType() { return tileType; }

SDL_Rect& Tile::getTileRect() { return tileRect; }

int Tile::getX() { return tileRect.x; }
int Tile::getY() { return tileRect.y; }

//getters AND setters
bool Tile::isSolid() { return solid; };
void Tile::isSolid(bool solid) { this->solid = solid; }