#include "KMGameObjectsHandler.h"

//loads objects into its vector
bool KMGameObjectsHandler::loadObjectsVector(std::string path) {

	//clear up the vector
	std::vector<std::unique_ptr<KMGameObject>> tempVector;
	objects.swap(tempVector);
	objects.clear();
	noOfPads = 0;

	bool success = true;

	//open file with objects data
	std::ifstream objectsFile(path.c_str());
	if (objectsFile.is_open()) {


		//temp variables to store data
		int x;
		int y;
		int type;
		int rotation;
		int flip;


		//load number of objects
		int noOfObjects = -1;
		objectsFile >> noOfObjects;

		//I do not know if clearing the vector destroys the objects this is kinda scary
		//load objects into object vector
		for (int i = 0; i < noOfObjects; i++) {


			objectsFile >> x;
			objectsFile >> y;
			objectsFile >> type;
			objectsFile >> rotation;
			objectsFile >> flip;
			

			//specials
			int maxFrames = 300;
			if (type == Objects::PAD) { objectsFile >> maxFrames; }

			if (objectsFile.fail()) { std::cout << "Failed insertion from file! SDL Error: " << SDL_Error << " \n"; success = false; break; }



			//check validity before loading objects
			if (x < 0 || y < 0 || rotation < 0 || rotation > 90) {
				std::cout << "Invalid object at: " << i << " \n";
				success = false;
				break;
			}
			else {

				//FOR OBJECTS
				switch (type) {

				//special objects
				case Objects::PAD: objects.push_back(std::unique_ptr<KMGameObject>(new Pad(x, y, rotation, flip,maxFrames, &noOfPads))); noOfPads++; break;
				
				//regular objects
				case Objects::DOOR: objects.push_back(std::unique_ptr<KMGameObject>(new Door(x, y, rotation, flip, room, &noOfPads))); break;
				case Objects::SPIKES: objects.push_back(std::unique_ptr<KMGameObject>(new Spikes(x, y, rotation, flip))); break;
				case Objects::STALAG: objects.push_back(std::unique_ptr<KMGameObject>(new Stalag(x, y, rotation, flip))); break;
				case Objects::GROUND_SPIKE: objects.push_back(std::unique_ptr<KMGameObject>(new Spike(x, y, rotation, flip, 0))); break;
				case Objects::WALL_SPIKE: objects.push_back(std::unique_ptr<KMGameObject>(new Spike(x, y, rotation, flip, 1))); break;
				case Objects::ROOF_SPIKE: objects.push_back(std::unique_ptr<KMGameObject>(new Spike(x, y, rotation, flip, 2))); break;
				case Objects::LAVA_POOL_EDGE: objects.push_back(std::unique_ptr<KMGameObject>(new LavaPool(x, y, rotation, flip, 0))); break;					
				case Objects::LAVA_POOL_MIDDLE: objects.push_back(std::unique_ptr<KMGameObject>(new LavaPool(x, y, rotation, flip, 1))); break;
				case Objects::LAVA_POOL_EDGE2: objects.push_back(std::unique_ptr<KMGameObject>(new LavaPool(x, y, rotation, flip, 2))); break;
				case Objects::LAVA_POOL_MIDDLE2: objects.push_back(std::unique_ptr<KMGameObject>(new LavaPool(x, y, rotation, flip, 3))); break;
				case Objects::LAVA_POOL_ALONE: objects.push_back(std::unique_ptr<KMGameObject>(new LavaPool(x, y, rotation, flip, 4))); break;
					
				}
					
			}
		}
	}
	else {
		std::cout << "Failed to open objects file at: " << path << "\n";
		success = false;
	}
	//close the file
	objectsFile.close();

	//wrap up with object loading

	return success;
}

bool KMGameObjectsHandler::loadObjectsVector(int room) {

	std::stringstream path;
	path << "files/objs/room" << room << ".aog";
	return loadObjectsVector(path.str().c_str());

}

void KMGameObjectsHandler::handleObjectCollisions(float timeStep) {
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->handleCollision(*husk);
	}
}


void KMGameObjectsHandler::renderObjects(SDL_Rect camera) {

	for (int i = 0; i < objects.size(); i++) {

		SDL_Rect animRect = objects[i]->getAnimRect();

		if (CHandler::checkCollision(animRect, camera)) {
			objects[i]->render(camera);
		}
	}
}

//setters
void KMGameObjectsHandler::setHusk(KMPlayerCharacter* husk) {
	this->husk = husk;
}

void KMGameObjectsHandler::setRoom(int* room) {
	this->room = room;
}