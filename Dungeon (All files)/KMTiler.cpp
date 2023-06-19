#include "KMTiler.h"

KMTiler::KMTiler() {
	roomType = -99;
}


void KMTiler::loadTileClips(int TILESET_WIDTH, int TILESET_HEIGHT, int NO_OF_CLIPS, int room) {
	int currentRoomType = -1;
	if (room > 6) { currentRoomType = 3;}
	else if (room > 3) { currentRoomType = 2;}
	else { currentRoomType = 1;}


	if (roomType != currentRoomType) {
		int clipsCreated = 0;
		while (clipsCreated < NO_OF_CLIPS) {
			for (int row = 0; row < TILESET_HEIGHT; row++) {
				for (int col = 0; col < TILESET_WIDTH; col++) {
					int x = col * TILE_DIMENSION;
					int y = row * TILE_DIMENSION;
					int clipWidth = TILE_WIDTH;
					int clipHeight = TILE_HEIGHT;

					clipsVector.push_back({ x, y, clipWidth, clipHeight });
					clipsCreated++;
				}
			}
		}
	}
}

bool KMTiler :: loadTilesetTexture(int room) {

	bool success = true;

	//set roomType
	int currentRoomType = -1;
	if (room > 6) { currentRoomType = 3; }
	else if (room > 3) { currentRoomType = 2; }
	else { currentRoomType = 1; }

	//only the last funnctions from KMTILER called in the loader function, i.e. load tileset textures, can change the roomType
	if (roomType != currentRoomType) {
		roomType = currentRoomType;

		//free old tileset
		tilesetTexture.free();

		switch (currentRoomType) {
		
		case 1:
			if (!tilesetTexture.loadFromImage("files/tilesets/paleTileset.png")) {
				std::cout << "Failed to load pale tileset texture!"; success = false;
			}
			break;
				
		case 2:
			if (!tilesetTexture.loadFromImage("files/tilesets/blueTileset.png")) {
				std::cout << "Failed to load blue tileset textue!"; success = false;
			}
			break;

		case 3:
			if (!tilesetTexture.loadFromImage("files/tilesets/redTileset.png")) {
				std::cout << "Failed to load red tileset texture!"; success = false;
			}
			break;
		}
	}

	return success;
}



bool KMTiler::loadTiles(KMPlayerCharacter& husk, int room) {

	//clean up tiles vector
	std::vector<std::vector <Tile >> tempTiles;
	tiles.swap(tempTiles);
	tiles.resize(0);

	//set highestSolidTile 
	{
		if (room > 6) { highestSolidTile = 23; }
		else if (room > 3) { highestSolidTile = 23; }
		else { highestSolidTile = 23; }
	}

	std::stringstream roomName;
	roomName << "files/rooms/room" << room << ".aog";

	bool success = true;

	//open map file form path
	std::ifstream mapFile(roomName.str().c_str());
	if (!mapFile.is_open()) {
		std::cout << "Failed to open map file!";
		success = false;
	}
	//if file opened successfully
	else {

		//load tilemap width and height
		int TILEMAP_WIDTH; mapFile >> TILEMAP_WIDTH; mapFile.ignore();
		int TILEMAP_HEIGHT; mapFile >> TILEMAP_HEIGHT; mapFile.ignore();
		
		levelWidth = TILEMAP_WIDTH * TILE_WIDTH;
		levelHeight = TILEMAP_HEIGHT * TILE_HEIGHT;

		//load and set spawn point
		float spawnX; mapFile >> spawnX; mapFile.ignore();
		float spawnY; mapFile >> spawnY; mapFile.ignore();

		husk.setSpawnX(spawnX);
		husk.setSpawnY(spawnY);
		husk.shiftCollider();

		//positions of tiles
		int x = -1;
		int y = -1;

		for (int row = 0; row < TILEMAP_HEIGHT; row++) {

			std::vector<Tile> rowVector;

			for (int col = 0; col < TILEMAP_WIDTH; col++) {

				int type = -1;

				//get coords, type and rotation

				x = col * 16;
				y = row * 16;


				mapFile >> type;
				mapFile.ignore();

				//check validity and create tile
				if (type >= -1) {
					rowVector.push_back(Tile(x, y, type));
					if (type <= highestSolidTile) { rowVector[col].isSolid(true); }
				}
				else {
					std::cout << "failed to validate tile: " << row << " " << col << "\n";
					success = false;
					break;
				}

				//if failed to load tile
				if (mapFile.fail()) {
					std::cout << "failed to load tile: " << row << " " << col << "\n";
					success = false;
					break;
				}
			}
			tiles.push_back(rowVector);
		}
		mapFile.close();
	}

	return success;

}

void KMTiler::loadTileRects(std::string path) {

	SDL_RWops* rectsFile = SDL_RWFromFile(path.c_str(), "r+b");
	int eof = 1;
	int i = 1;
	while (eof != 0) {
		tileRects.resize(i);
		eof = SDL_RWread(rectsFile, &tileRects[int(i - 1)], sizeof(SDL_Rect), 1);
		i++;
	}

	SDL_RWclose(rectsFile);
}

void KMTiler::loadTileRects(int room) {

	std::stringstream roomName;
	roomName << "files/rooms/room" << room << ".bin";

	loadTileRects(roomName.str().c_str());
}

void KMTiler::renderTiles(SDL_Rect camera) {
	for (int row = 0; row < tiles.size(); row++) {
		for (int col = 0; col < tiles[0].size(); col++) {
			//render if within camera range
			if (CHandler::checkCollision(camera, tiles[row][col].getTileRect())) {
				tiles[row][col].render(&tilesetTexture, &clipsVector, camera);
			}
		}	
	}
	
}



//loads vertical rects of tile into given vector
void KMTiler :: loadBigRects(std::vector<SDL_Rect>& rectVector, std::string path) {
	SDL_RWops* bigRectsFile = SDL_RWFromFile(path.c_str(), "r+b");
	int eof = 1;
	int i = 1;
	while (eof != 0) {
		rectVector.resize(i);
		eof = SDL_RWread(bigRectsFile, &rectVector[(i - 1)], sizeof(SDL_Rect), 1);
		i++;
	}

	SDL_RWclose(bigRectsFile);
}



//getters
int KMTiler::getHighestSolidTile() { return highestSolidTile; }
std::vector<SDL_Rect>& KMTiler::getTileRects() { return tileRects; }
int KMTiler::getLevelWidth() { return levelWidth; }
int KMTiler::getLevelHeight() { return levelHeight; }

