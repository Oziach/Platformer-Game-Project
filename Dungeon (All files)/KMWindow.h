#pragma once
#include<SDL.h>
#include<iostream>

class KMWindow {
public:
	KMWindow(const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
	~KMWindow();
	SDL_Renderer* createRenderer();

	bool createWindow(std::string name);
	void handleEvents(SDL_Event& e, SDL_Renderer* kmRenderer, bool& quit);
	

	bool isFullscreen();
	bool isMinimized();

	int getWindowWidth();
	int getWindowHeight();

	void free();

private:

	SDL_Window* kmWindow;

	int WINDOW_WIDTH;
	int WINDOW_HEIGHT;

	bool fullscreen;
	bool minimized;
};

