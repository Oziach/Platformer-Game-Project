#include "Clock.h"

//initialize variables
Clock::Clock() {
	startTicks = 0;
	started = false;
}

void Clock::start() {
	started = true;
	startTicks = SDL_GetTicks();
}

Uint32 Clock::getTicks() {
	if (started) {
		return (SDL_GetTicks() - startTicks);
	}
}

void Clock::stop() {
	started = false;
	startTicks = 0;
}