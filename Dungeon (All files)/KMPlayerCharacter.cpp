#include "KMPlayerCharacter.h"
#include"KMGameObjectsHandler.h"
#include "KMNPCsHandler.h"

extern KMGameObjectsHandler kmObjectsHandler;
extern KMNPCsHandler kmNPCsHandler;

void loadMedia();

class KMPlayerCharacter;

KMPlayerCharacter::KMPlayerCharacter() {
	shiftCollider();

	for (int i = 0; i < 9; i++) {
		clips.push_back({ i * C_WIDTH, 0, C_WIDTH, C_HEIGHT });
	}

}



void KMPlayerCharacter::handleHorizontalMovement(float timeStep) {
	const Uint8* keystates = SDL_GetKeyboardState(NULL);

	prevXPos = xPos;

	if (keystates[SDL_SCANCODE_RIGHT]) {

		facingRight = true;

		if (!controlLocked) {			
			xPos += X_VEL * timeStep;
		}
		if (wallClinging == 1 && wallReleaseCountdown == -1.f) {wallReleaseCountdown = -0.05f; }


	}

	if (keystates[SDL_SCANCODE_LEFT]) {

		facingRight = false;

		if (!controlLocked) {
			xPos -= X_VEL * timeStep;
		}
		if (wallClinging == -1 && wallReleaseCountdown == -1.f) { wallReleaseCountdown = -0.05f; }

		
	}

	rawXVel = xPos - prevXPos;
}

void KMPlayerCharacter::handleJump() {

	const Uint8* keystates = SDL_GetKeyboardState(NULL);


		if (keystates[SDL_SCANCODE_DOWN]) {
			wallClinging = 0; controlLocked = false; wallReleaseCountdown = -1;
		}


}
void KMPlayerCharacter::handleWalljump(float timeStep) {


	if (walljumpCountdown == -0.20f) {

		walljumpCountdown += timeStep;

			walljumpsLeft -= 1;

			yVel = 0; yVel -= WALLJUMP_Y_VEL;
			externalXVel += WALLJUMP_X_VEL * wallClinging;

			wallClinging = 0; wallReleaseCountdown = -1;
		
	}

	if (walljumpCountdown >= 0) {
		walljumpCountdown = -1.f;
		controlLocked = false;
		externalXVel = 0;
	}

	//if walljumping
	if (walljumpCountdown > -0.2f) {
		walljumpCountdown += timeStep;
	}
}

void KMPlayerCharacter::handleWallCling(float timeStep) {
	
	int wallhumpRange = clingRect.y + clingRect.h - 4; int wallhumpTop = clingRect.y - 1;

	if (wallClinging != 0) {
		//wallClinging = 0; controlLocked = false; wallReleaseCountdown = -1;
		if (yPos > wallhumpRange || yPos < wallhumpTop) {
			wallClinging = 0; controlLocked = false; wallReleaseCountdown = -1;
			walljumpCountdown = -1.f;
		}

		if (wallClinging != 0) {

			controlLocked = true;
			yVel = 25;

			//if clinging left wall
			if (wallClinging == -1) {
				if (clingRect.x != collider.x + collider.w) {
					wallClinging = 0; controlLocked = false; wallReleaseCountdown = -1;
				}
			}
			//else if clinging right wall
			else if (wallClinging == 1) {
				if (clingRect.x + clingRect.w != collider.x) {
					wallClinging = 0; controlLocked = false; wallReleaseCountdown = -1;
				}
			}


		}

		if (wallReleaseCountdown < 0 && wallReleaseCountdown != -1) {
			wallReleaseCountdown += timeStep;
		}
		else if (wallReleaseCountdown >= 0) {

			controlLocked = false;
			wallReleaseCountdown = -1;
		}

	}
}

void KMPlayerCharacter::respawn() {
	yVel = 0;
	wallReleaseCountdown = -1;
	controlLocked = false;
	wallClinging = false;
	walljumpsLeft = 3;
	externalXVel = 0;

	loadMedia();
	prevXPos = xPos;

	SDL_Delay(300);
}

void KMPlayerCharacter::handleDeath() {
	respawn();
}

void KMPlayerCharacter::handleKeyboardInput(SDL_Event& e, float timeStep) {


	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {

		//jump
		if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_s) {

			if (grounded) {
				yVel = 0;
				yVel -= JUMP_VEL;
			}

			//walljump
			if (wallClinging) {

				if (walljumpsLeft > 0) { walljumpCountdown = -0.2f; }
			}
		}

		if (e.key.keysym.sym == SDLK_r) {
			respawn();
		}

	}
	
	//up release
	if (e.type == SDL_KEYUP) {

		if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_s) {
			if (yVel < 25) {
				yVel = 25;
			}
		}
	}
}

void KMPlayerCharacter::move(std::vector <SDL_Rect> rects, int highestSolidTile, float timeStep) {


	handleJump();
	handleWallCling(timeStep);
	handleWalljump(timeStep);

	yVel += GRAVITY * timeStep;
	yPos += float(yVel * timeStep);

	handleHorizontalMovement(timeStep);
	xPos += externalXVel * timeStep;


	shiftCollider();


	grounded = false;

	handleTileCollision(rects, timeStep);
	kmObjectsHandler.handleObjectCollisions(timeStep);
	kmNPCsHandler.handleNPCTriggers(timeStep);
	kmNPCsHandler.handleNPCCollisions(timeStep);
	

}

void KMPlayerCharacter::handleTileCollision(std::vector <SDL_Rect> tileRects, float timeStep) {

	for (int i = 0; i < tileRects.size(); i++) {

		SDL_Rect rect = tileRects[i];

			if (CHandler::checkCollision(collider, rect)) {

				CHandler::CollisionDirection direction = CHandler::getCollisionDirection(*this, rect, timeStep); 
				if (direction != CHandler::NO_COLLISION) {


					if (direction == CHandler::LEFT_COLLISION) {

						if (yVel > 0) { wallClinging = -1; }
						clingRect = tileRects[i];

						xPos = float(rect.x - collider.w);
						shiftCollider();

					}
					else if (direction == CHandler::RIGHT_COLLISION) {

						if (yVel > 0) { wallClinging = 1; }
						clingRect = tileRects[i];
	

						xPos = float(rect.x + rect.w);
						shiftCollider();
					}

					if (direction == CHandler::BOTTOM_COLLISION) {
						yPos = float(rect.y + rect.h);
						yVel = 0;
						shiftCollider();
					}

					else if (direction == CHandler::TOP_COLLISION) {
						
						grounded = true;
						externalXVel = 0;
						controlLocked = false;
						wallClinging = 0;  wallReleaseCountdown = -1;
						walljumpsLeft = 3; walljumpCountdown = -1.f;

						yPos = float(rect.y - collider.h + 0.999f);
						yVel = 0;
						shiftCollider();
					}
				}
			}
	}
}

void KMPlayerCharacter::render(SDL_Rect& camera) {

	if (rawXVel > 0) { facingRight = true; } else if (rawXVel < 0) { facingRight = false; }

	SDL_RendererFlip flip = SDL_FLIP_NONE;
	flip = facingRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

	if (grounded && rawXVel != 0) {
		if (animationFrame != 1 && animationFrame != 2) { animationFrame = 1; }

		huskTexture.render(int(xPos) - camera.x, int(yPos) - camera.y, &clips[animationFrame], NULL, NULL, flip);

		if (frameCounter % 8 == 0) {
			animationFrame++;
		}

		//reset to first frame of walk after cycle
		if (animationFrame == 5) {
			animationFrame = 1;
		}

	}

	//if jumping
	else if (!grounded && wallClinging == 0) {
		huskTexture.render(int(xPos) - camera.x, int(yPos) - camera.y, &clips[0], NULL, NULL, flip);
	}

	else if (!grounded && wallClinging != 0) {
		if (wallClinging == 1) { flip = SDL_FLIP_NONE; } else if (wallClinging == -1) { flip = SDL_FLIP_HORIZONTAL; }
		//render
		huskTexture.render(int(xPos) - camera.x, int(yPos) - camera.y, &clips[8], NULL, NULL, flip);
	}

	else if (rawXVel == 0) {
		if (animationFrame != 5 && animationFrame != 6) { animationFrame = 5; }
		huskTexture.render(int(xPos) - camera.x, int(yPos) - camera.y, &clips[animationFrame], NULL, NULL, flip);
		if (frameCounter % 10 == 0) {
			animationFrame++;
		}
		if (animationFrame == 7) {
			animationFrame = 5;
		}
	}

	frameCounter++;
	if (frameCounter == 600001) {
		frameCounter = 1;
	}
}

void KMPlayerCharacter::shiftCollider() { collider.x = int(xPos); collider.y = int(yPos); }

//Center camera around player
void KMPlayerCharacter::centerCamera(SDL_Rect& camera, const int LEVEL_WIDTH, const int LEVEL_HEIGHT) {

	camera.x = (int(xPos) + C_WIDTH / 2) - camera.w / 2;
	camera.y = (int(yPos) + C_HEIGHT / 2) - camera.h / 2;


	if (camera.x < 0) { camera.x = 0; }
	if (camera.y < 0) { camera.y = 0; }
	if (camera.x + camera.w > LEVEL_WIDTH) { camera.x = LEVEL_WIDTH - camera.w; }
	if (camera.y + camera.h > LEVEL_HEIGHT) { camera.y = LEVEL_HEIGHT- camera.h; }


}

//setters
void KMPlayerCharacter::setKMPlayerCharacterTexture(std::string path) { huskTexture.loadFromImage(path);}

void KMPlayerCharacter::setSpawnX(float spawnX) { xPos = spawnX; /*lastXPos = xPos;*/ }
void KMPlayerCharacter::setSpawnY(float spawnY) { yPos = spawnY; /*lastYPos = yPos;*/ }
void KMPlayerCharacter::setXPos(float xPos) { this->xPos = xPos; }
void KMPlayerCharacter::setYPos(float yPos) { this->yPos = yPos; }
void KMPlayerCharacter::setYVel(float yVel) { this->yVel = yVel; }

//getters
float KMPlayerCharacter::getRawXVel() { return rawXVel; }
float KMPlayerCharacter::getYVel() { return yVel; }
float KMPlayerCharacter::getXPos() { return xPos; }
float KMPlayerCharacter::getYPos() { return yPos; }
//float KMPlayerCharacter::getLastXPos() { return lastXPos; }
//float KMPlayerCharacter::getLastYPos() { return lastYPos; }
float KMPlayerCharacter::isGrounded() { return grounded; }
void KMPlayerCharacter::setGrounded(bool grounded) { this->grounded = grounded; }
SDL_Rect& KMPlayerCharacter::getCollider() { return collider; }
