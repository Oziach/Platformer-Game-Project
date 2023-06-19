#pragma once
#include<SDL.h>
class Clock {

private:
	int startTicks;
	bool started;

public:
	Clock();
	Uint32 getTicks();
	void start();
	void stop();

};

