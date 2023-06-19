#pragma once
#include<SDL.h>
#include<vector>
#include<cmath>

#include"KMTexture.h"
#include"Tile.h"
#include"CHandler.h"


class KMPlayerCharacter
{
private:
	KMTexture huskTexture;
	std::vector<SDL_Rect> clips;

	const int C_WIDTH = 6;
	const int C_HEIGHT = 13;
	

	const float X_VEL = 70;
	const float JUMP_VEL = 125;
	const float WALLJUMP_Y_VEL = 125;
	const float WALLJUMP_X_VEL = 50;
	const float GRAVITY = 400;

	//STATE

	float xPos = 0; float prevXPos = 0;
	float yPos = 0;

	float rawXVel = xPos - prevXPos;
	float externalXVel = 0;
	float yVel = 0;

	SDL_Rect collider = {int(xPos), int(yPos), C_WIDTH, C_HEIGHT };


	bool controlLocked = false;
	bool grounded = false;

	int wallClinging = 0; //-1 = left, 1 = right, 0 = false
	SDL_Rect clingRect = {-1,-1,-1,-1};
	float wallReleaseCountdown = 0;

	float walljumpsLeft = 3;
	float walljumpCountdown = 0;

	//animation
	bool facingRight = true;
	int animationFrame = 0;
	int frameCounter = 0;

public:
	KMPlayerCharacter();

	//input stuff
	void handleKeyboardInput(SDL_Event& e, float timeStep);
	void handleHorizontalMovement(float timeStep);

	//handling stuff
	void move(std::vector <SDL_Rect> rects, int highestSolidTile, float timeStep);
	void handleTileCollision(std::vector <SDL_Rect> tileRects, float timeStep);
	void handleDeath();
	void handleJump();
	void handleWalljump(float timeStep);
	void handleWallCling(float timeStep);

	//rendering stuff
	void render(SDL_Rect& camera);
	void setKMPlayerCharacterTexture(std::string path);

	//misc
	void respawn();
	void shiftCollider();
	void centerCamera(SDL_Rect& camera, const int LEVEL_WIDTH, const int LEVEL_HEIGHT);

	//setters
	void setSpawnX(float spawnX);
	void setSpawnY(float spawnY);
	void setGrounded(bool grounded);
	void setXPos(float xPos);
	void setYPos(float yPos);
	void setYVel(float yVel);

	//getters
	float getXPos();
	float getYPos();
	/*float getLastXPos();
	float getLastYPos();*/
	float getXVel();
	float getRawXVel();
	float getYVel();
	float isGrounded();
	SDL_Rect& getCollider();
};

