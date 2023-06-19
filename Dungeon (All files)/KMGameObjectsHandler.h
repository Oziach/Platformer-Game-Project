	#pragma once
#include<vector>
#include<fstream>
#include<iostream>
#include<sstream>


#include"KMGameObject.h"
#include"Door.h"
#include"Spike.h"
#include"LavaPool.h"
#include"Spikes.h"
#include"Stalag.h"
#include"Pad.h"


class KMGameObjectsHandler {

private:

	std::vector<std::unique_ptr<KMGameObject>> objects;
	KMPlayerCharacter* husk = NULL;
	int* room = NULL;
	int noOfPads = 0;

public:

	void handleObjectCollisions(float timeStep);

	bool loadObjectsVector(std::string path);
	bool loadObjectsVector(int room);

	void renderObjects(SDL_Rect camera);


		enum Objects {
			PAD = -1, //-1
			DOOR = 0, //0
			SPIKES = 1, //1
			STALAG = 2, //2
			GROUND_SPIKE = 3, //3
			WALL_SPIKE = 4, //4
			ROOF_SPIKE = 5, //5
			LAVA_POOL_EDGE = 6, //6
			LAVA_POOL_MIDDLE = 7, //7
			LAVA_POOL_EDGE2 = 8, //8
			LAVA_POOL_MIDDLE2 = 9, //9
			LAVA_POOL_ALONE = 10, //10		
		};




	//setters
	void setHusk(KMPlayerCharacter* husk);
	void setRoom(int* room);

};

