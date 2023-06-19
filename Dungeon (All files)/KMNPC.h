#pragma once
#include "KMGameObject.h"
class KMNPC :  public KMGameObject {

private:
	
	int activeClip = 0;

protected: SDL_Rect triggerBox = { 0,0,0,0 };
		   bool active = false;

public:
	virtual void move(KMPlayerCharacter& husk, float timeStep) {};
	virtual void moveActive(float timeStep) {};
	virtual void movePassive(float timeStep) {};
	virtual void renderNPC(SDL_Rect camera) {};
	virtual void renderActive(SDL_Rect camera) {};
	virtual void renderPassive(SDL_Rect camera) {};
	virtual void handleTrigger(KMPlayerCharacter& husk, float timeStep);
	virtual void moveTriggerBox() {};

	void setActiveClip(int n);
	bool isActive();
};

