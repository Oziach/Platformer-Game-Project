#include "KMNPC.h"


void KMNPC::setActiveClip(int n) {	activeClip = n;}
bool KMNPC::isActive() { return active; }

void KMNPC::handleTrigger(KMPlayerCharacter& husk, float timeStep) {
	if (CHandler::checkCollision(husk.getCollider(), triggerBox)) {
		active = true;
	}
	else {
		active = false;
	}
}
