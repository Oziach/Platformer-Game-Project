#include "KMGameObject.h"



void KMGameObject::render(SDL_Rect camera, int minClip , int maxClip) {
	
	
	if (maxClip == 0) { maxClip = s_clips->size() - 1; }
	if (frame < minClip * framesPerClip) { frame = minClip * framesPerClip; }

	
	if (framesPerClip != 0) {	
		int clipToRender = frame / framesPerClip;
		if (clipToRender > maxClip) { clipToRender = minClip; }
		s_spritesheet->render(int(xPos - camera.x), int(yPos - camera.y), &(s_clips->at(clipToRender)), rotation, NULL, flip);	
	}
	else {
		s_spritesheet->render(int(xPos - camera.x), int(yPos - camera.y), &(s_clips->at(0)), rotation, NULL, flip);
	}
	
	frame++;
	if (frame >= framesPerLoop) { frame = minClip * framesPerClip; }

	
}


void KMGameObject::loadClips(std::vector<SDL_Rect>& clips, int noOfClips) {

	std::vector<SDL_Rect> tempVector;
	clips.swap(tempVector);
	clips.clear();

	for (int i = 0; i < noOfClips; i++) {
		clips.push_back({ i * width, 0, width, height });
	}

}

void KMGameObject::handleCollision(KMPlayerCharacter& husk) {
	if (CHandler::checkCollision(husk.getCollider(), hitbox)) {
		husk.handleDeath();
	}
}

void KMGameObject::calculateFramesPerLoop() {
	framesPerLoop = (framesPerClip * s_clips->size()) + framesBetweenLoops;
}

SDL_Rect KMGameObject:: getAnimRect() {
	return { xPos, yPos, width, height };
}