#pragma once
#include<iostream>
#include<fstream>
#include<SDL.h>
#include"MButton.h"
#include<vector>
#include"KMTexture.h"
#include"KMWindow.h"
#include"KMPlayerCharacter.h"
#include<sstream>

extern KMWindow kmWindow;

class Menu {

private:

	const int CAMERA_WIDTH = 256;
	const int CAMERA_HEIGHT = 144;

	int& room;
	int maxRoom;

	std::vector<MButton> menuButtons;
	std::vector<SDL_Rect> menuButtonClips;

	std::vector<MButton> roomButtons;
	std::vector<SDL_Rect> roomButtonClips;


	KMTexture menuButtonsTexture;
	KMTexture roomButtonsTexture;
	KMTexture stringHighlightTexture;
	KMTexture intHighlightTexture;

	bool selectScreen;
	bool menu;
	bool started = true;

	SDL_Rect highlightRect;
	int stringHighlight;
	int intHighlight;

public:
	Menu(int& room);


	void renderMenu(KMPlayerCharacter &husk);
	void handleMenuEvents(SDL_Event &e, bool& quit, KMWindow& window, SDL_Renderer* kmRenderer);
	void updateRoomButtons();

	bool loadMenuTextures(KMPlayerCharacter& husk);
	void freeMenuTextures();

	bool onSelectScreen();
	bool inMenu();
	void setMenu(bool menuStatus);
	bool isStarted();

	void loadMaxRoom();
	void setMaxRoom(int eMaxRoom);
	int getMaxRoom() { return maxRoom; }

	enum menuButtons {
		 START, //0
	     SELECT , //1
		 QUIT, //2
		 HIGHLIGHT //3
	};
};

