#include "KMWindow.h"


//initialize variables
KMWindow::KMWindow(const int SCREEN_WIDTH, const int SCREEN_HEIGHT) {


	kmWindow = NULL;
	WINDOW_WIDTH = SCREEN_WIDTH;
	WINDOW_HEIGHT = SCREEN_HEIGHT;
	fullscreen = false;
	minimized = false;

}

//Free memory
KMWindow::~KMWindow() {
	free();
}


//Create and return pointer to renderer for window
SDL_Renderer* KMWindow::createRenderer() {
	return SDL_CreateRenderer(kmWindow, -1, SDL_RENDERER_ACCELERATED);
}


//Create window
bool KMWindow::createWindow(std::string name) {
	
	//success variable
	bool success = true;

	//create window 
	kmWindow = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	//check failure
	if (kmWindow == NULL) {
		std::cout << "Failed to create window! SDL_Error: " << SDL_GetError();
		success = false;
	}

	return success;
}


//handle input
void KMWindow::handleEvents(SDL_Event& e, SDL_Renderer* kmRenderer, bool& quit) {
	
	//If cross is clicked
	if (e.type == SDL_QUIT) {
		quit = true;
	} 

	//If not quit
	else {

		//If window event
		if (e.type == SDL_WINDOWEVENT) {

			if (e.window.event == SDL_WINDOWEVENT_RESIZED) {

				WINDOW_WIDTH = e.window.data1;
				WINDOW_HEIGHT = e.window.data2;
				SDL_RenderPresent(kmRenderer);

			}
			
			//If shown
			if (e.window.event == SDL_WINDOWEVENT_SHOWN) {

				minimized = false;
			}

			//if exposed
			if (e.window.event == SDL_WINDOWEVENT_EXPOSED) {
				WINDOW_WIDTH = e.window.data1;
				WINDOW_HEIGHT = e.window.data2;
				minimized = false;
				SDL_RenderPresent(kmRenderer);
			}

			//if maximized
			if (e.window.event == SDL_WINDOWEVENT_MAXIMIZED) {
				minimized = false;
				WINDOW_WIDTH = e.window.data1;
				WINDOW_HEIGHT = e.window.data2;
				SDL_RenderPresent(kmRenderer);
			}

			//if minimized
			if (e.window.event == SDL_WINDOWEVENT_MINIMIZED) {
				minimized = true;
			}

		}

		//if key press
		else if (e.type == SDL_KEYDOWN) {

			//if return and alt pressed together
			if (e.key.keysym.sym == SDLK_RETURN && (SDL_GetModState() & KMOD_ALT )) {

				//toggle fullscreen off if on
				if (fullscreen) {
					SDL_SetWindowFullscreen(kmWindow, SDL_FALSE);
					fullscreen = false;
				}
				//toggle fullscreen on if off
				else {
					
					SDL_DisplayMode dM;
					SDL_GetCurrentDisplayMode(0, &dM);

					SDL_SetWindowSize(kmWindow, dM.w, dM.h);

					SDL_SetWindowFullscreen(kmWindow, SDL_WINDOW_FULLSCREEN);
					fullscreen = true;
				}
			}

			if (e.key.keysym.sym == SDLK_TAB && (SDL_GetModState() & KMOD_ALT)) {
				minimized = true;
				SDL_SetWindowFullscreen(kmWindow, SDL_FALSE);
				fullscreen = false;
			}
		}
	}
}


//getter functions
bool KMWindow::isFullscreen() { return fullscreen; }
bool KMWindow::isMinimized() { return minimized; }


//free function
void KMWindow::free() {

	SDL_DestroyWindow(kmWindow);
	kmWindow = NULL;
	fullscreen = false;
	minimized = false;
	WINDOW_WIDTH = 0;
	WINDOW_HEIGHT = 0;

}


int KMWindow::getWindowWidth() { return WINDOW_WIDTH; }
int KMWindow::getWindowHeight() { return WINDOW_HEIGHT; }