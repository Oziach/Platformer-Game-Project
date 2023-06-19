#include<iostream>
#include<SDL.h>
#include<SDL_image.h>

#include"KMWindow.h"
#include"KMTexture.h"
#include"Clock.h"
#include"KMPlayerCharacter.h"
#include"KMTiler.h"
#include"Menu.h"
#include"KMGameObjectsHandler.h"
#include"KMNPCsHandler.h"



//global consts
const int SCREEN_WIDTH = 256;
const int SCREEN_HEIGHT = 144;
const int CAMERA_WIDTH = 256;
const int CAMERA_HEIGHT = 144;

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

//global variables and objects

int room = 1;
SDL_Rect camera = { 0,0, CAMERA_WIDTH, CAMERA_HEIGHT };

KMWindow kmWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
SDL_Renderer* kmRenderer = NULL;

KMTiler kmTiler;
KMGameObjectsHandler kmObjectsHandler;
KMNPCsHandler kmNPCsHandler;
Menu menu(room);

KMPlayerCharacter husk;
KMTexture splash;


//global functions
void init() {

	bool success = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		success = false;
		std::cout << "Failed to init SDL_Video";
	}
	else {
	
		//create window
		if (!kmWindow.createWindow("Treasure Dungeon")) {
			std::cout << "Failed to create window!\n";
			success = false;
		}
		else {

			//create renderer
			kmRenderer = kmWindow.createRenderer();
			if (kmRenderer == NULL) {
				std::cout << "Failed to create renderer! SDL ERROR: " << SDL_GetError() << std::endl;
				success = false;
			}
			else {


				//boot SDL_image
				int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF;
				if ((IMG_Init((imgFlags)&imgFlags)) == 0) {
					std::cout << "Failed to init img! IMG ERROR: " << IMG_GetError();
					success = false;
				}
				else {
					//set texture filtering to nearest pixel
					SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

					//for proper upscaling
					SDL_RenderSetLogicalSize(kmRenderer, CAMERA_WIDTH, CAMERA_HEIGHT);

				}
			}
		}

	}	

	if (!success) { std::cout << "Failed to init!"; }

}

void loadMedia() {

	if (room < 1) { room = 1; }

	if (room <= 9) {

		kmTiler.loadTileClips(8, 4, 30, room);

		kmTiler.loadTileRects(room);

		if (!kmTiler.loadTiles(husk, room)) { std::cout << "Failed to load tiles!\n"; }

		if (!kmTiler.loadTilesetTexture(room)) { std::cout << "Failed to load tileset texture!\n"; }

		if (!kmObjectsHandler.loadObjectsVector(room)) { std::cout << "Failed to load objects in room: " << room << "\n"; }
		if (!kmNPCsHandler.loadNPCsVector(room)) { std::cout << "Failed to load NPCs in room: " << room << "\n"; }
		
	}
	splash.loadFromImage("sprites/splash.png");
}

void handleMenu(Clock& frameTimer, SDL_Event& e, bool& quit) {

	menu.loadMaxRoom();
	menu.loadMenuTextures(husk);
	menu.updateRoomButtons();
	husk.respawn();

	while (menu.inMenu()) {
		frameTimer.start();

		//menu stuff
		menu.handleMenuEvents(e, quit, kmWindow, kmRenderer);

		//handle menu events

		//if exited menu
		if (!menu.inMenu()) {
			menu.freeMenuTextures();

			//if started
			if (menu.isStarted()) {

				loadMedia();
			}

			else if (!menu.isStarted()) {
				break;
			}
			break;
		}

		//render and present
		SDL_SetRenderDrawColor(kmRenderer, 0xCC, 0xCC, 0xCC, 0xFF);
		SDL_RenderClear(kmRenderer);

		menu.renderMenu(husk);
		SDL_RenderPresent(kmRenderer);

		//cap framerate
		int frameTicks = frameTimer.getTicks();
		//limit framerate to 60
		if (frameTicks < SCREEN_TICKS_PER_FRAME) {
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
		}

	}

}

void exit() {
	
	IMG_Quit();
	SDL_Quit();
}


 
int main(int argc, char* args[]) {

	init();

	husk.setKMPlayerCharacterTexture("sprites/Husk.png");
	kmObjectsHandler.setHusk(&husk);
	kmNPCsHandler.setHusk(&husk);
	kmObjectsHandler.setRoom(&room);
	kmNPCsHandler.setRoom(&room);

	loadMedia();

	SDL_Event e;
	bool quit = false;

	Clock clock;
	float timeStep = 0;


justBeforeMenu:
	handleMenu(clock, e, quit);

	//main loop
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {

			//menu
			{
				if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
					menu.setMenu(true);
					goto justBeforeMenu;
				}

				//code for demonstration
				if (e.type == SDL_KEYDOWN) {
					if (e.key.keysym.sym == SDLK_1) { room--; loadMedia(); }
					else if (e.key.keysym.sym == SDLK_2) { room++; loadMedia(); if (room > 10) { room = 10; }}		
					
				}
				
				kmWindow.handleEvents(e, NULL, quit);
				husk.handleKeyboardInput(e, timeStep);
			}
			
		}

		if (room != 10) {

			timeStep = clock.getTicks() / 1000.f;
			if (timeStep > 0.030) { timeStep = float(0.030); }

			//move
			husk.move(kmTiler.getTileRects(), kmTiler.getHighestSolidTile(), timeStep);
			kmNPCsHandler.handleNPCMovements(husk, timeStep);
			clock.start();

			husk.centerCamera(camera, kmTiler.getLevelWidth(), kmTiler.getLevelHeight());

			//render
			SDL_SetRenderDrawColor(kmRenderer, 0x00, 0x00, 0x00, 0xFF);
			SDL_RenderClear(kmRenderer);

			kmTiler.renderTiles(camera);
			kmObjectsHandler.renderObjects(camera);
			kmNPCsHandler.renderNPCs(camera);
			husk.render(camera);

			SDL_RenderPresent(kmRenderer);

		}

		else {

			SDL_SetRenderDrawColor(kmRenderer, 0x00, 0x00, 0x00, 0xFF);
			SDL_RenderClear(kmRenderer);
			splash.render(0, 0);
			SDL_RenderPresent(kmRenderer);
		}

		//limit framerate to 60
		{	
			int frameTicks = clock.getTicks();
			if (frameTicks < SCREEN_TICKS_PER_FRAME) {
				SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
			}
		}

		{
			if (husk.getYPos() > kmTiler.getLevelHeight()) { husk.respawn(); }
		}

	}

	exit();
	return 0;
}