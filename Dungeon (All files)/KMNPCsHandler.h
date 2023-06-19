#pragma once
#include<vector>
#include<fstream>
#include<sstream>

#include"KMNPC.h"
#include"Carnivore.h"
#include"SkullLord.h"

class KMNPCsHandler {

private:

	std::vector<std::unique_ptr<KMNPC>> npcs;
	KMPlayerCharacter* husk;
	int* room = NULL;

public:

	bool loadNPCsVector(std::string path);
	bool loadNPCsVector(int room);
	void handleNPCCollisions(float timeStep);
	void handleNPCTriggers(float timeStep);
	void handleNPCMovements(KMPlayerCharacter& husk, float timeStep);
	void renderNPCs(SDL_Rect camera);

	enum NPCs {
		CARNIVORE, //0
		SKULL_LORD, //1
	};

	//setters
	void setHusk(KMPlayerCharacter* husk);
	void setRoom(int* room);

};

