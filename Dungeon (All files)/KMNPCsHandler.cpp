#include "KMNPCsHandler.h"


//loads objects into its vector
bool KMNPCsHandler::loadNPCsVector(std::string path) {

	//clear up the vector
	std::vector<std::unique_ptr<KMNPC>> tempVector;
	npcs.swap(tempVector);
	npcs.clear();

	bool success = true;

	//open file with objects data
	std::ifstream npcsFile(path.c_str());
	if (npcsFile.is_open()) {


		//temp variables to store data
		int x;
		int y;
		int type;
		int rotation;
		int flip;


		//load number of objects
		int noOfNPCs = -1;
		npcsFile >> noOfNPCs;

		//I do not know if clearing the vector destroys the objects this is kinda scary
		//load objects into object vector
		for (int i = 0; i < noOfNPCs; i++) {


			npcsFile >> x;
			npcsFile >> y;
			npcsFile >> type;
			npcsFile >> rotation;
			npcsFile >> flip;


			if (npcsFile.fail()) { std::cout << "Failed insertion from file! SDL Error: " << SDL_Error << " \n"; success = false; break; }



			//check validity before loading objects
			if (x < 0 || y < 0 || rotation < 0 || rotation > 90) {
				std::cout << "Invalid npc at: " << i << " \n";
				success = false;
				break;
			}
			else {

				//FOR OBJECTS
				switch (type) {

				case NPCs::CARNIVORE: npcs.push_back(std::unique_ptr<KMNPC>(new Carnivore(x, y, rotation, flip))); break;
				case NPCs::SKULL_LORD: {
					int x, y, w, h; npcsFile >> x; npcsFile >> y; npcsFile >> w; npcsFile >> h;
					npcs.push_back(std::unique_ptr<KMNPC>(new SkullLord(x, y, rotation, flip, { x,y,w,h }))); break;
				}
				}

			}

		}
	}
	else {
		std::cout << "Failed to open npcs file at: " << path << "\n";
		success = false;
	}
	//close the file
	npcsFile.close();

	//wrap up with object loading

	return success;
}


bool KMNPCsHandler::loadNPCsVector(int room) {

	std::stringstream path;
	path << "files/npcs/room" << room << ".aog";
	return loadNPCsVector(path.str().c_str());

}

void KMNPCsHandler::handleNPCTriggers(float timeStep) {
	for (int i = 0; i < npcs.size(); i++) {
		npcs[i]->handleTrigger(*husk, timeStep);
	}
}

void KMNPCsHandler::handleNPCCollisions(float timeStep) {
	for (int i = 0; i < npcs.size(); i++) {
		npcs[i]->handleCollision(*husk);
	}
}

void KMNPCsHandler::handleNPCMovements(KMPlayerCharacter& husk, float timeStep) {
	for (int i = 0; i < npcs.size(); i++) {
		npcs[i]->move(husk, timeStep);
	}
}

void KMNPCsHandler::renderNPCs(SDL_Rect camera) {
	for (int i = 0; i < npcs.size(); i++) {
		npcs[i]->renderNPC(camera);
	}
}


//setters
void KMNPCsHandler::setHusk(KMPlayerCharacter* husk) {
	this->husk = husk;
}

void KMNPCsHandler::setRoom(int* room) {
	this->room = room;
}
