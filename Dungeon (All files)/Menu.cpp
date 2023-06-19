#include "Menu.h"

Menu::Menu(int& eRoom) : room(eRoom) {
	
	//for now by default, its at 1 in the file
	loadMaxRoom();
	selectScreen = false;
	menu = true;
	stringHighlight = -1;
	intHighlight = 0;
	
	highlightRect.h = 30;
	highlightRect.w = 72;
	highlightRect.x = 4;
	highlightRect.y = 4;

	//initialize all the damn buttons here.
	menuButtons.push_back(MButton( 96, 11, 64, 24, "START") ); //start button
	menuButtonClips.push_back({ 0,0, 64, 24 });

	menuButtons.push_back(MButton(96, 55, 64, 24, "SELECT")); //select button
	menuButtonClips.push_back({ 0, 24, 64, 24 });

	menuButtons.push_back(MButton(96, 102, 64, 24, "QUIT")); //quit button
	menuButtonClips.push_back({ 0, 48, 64, 24 });

	

	//create buttons with respect to max room

	//temp single room button clip
	for (int i = 0; i <= 2; i++) {
		roomButtonClips.push_back({ 0, 0, 16, 16 });
	}

	for (int i = 3; i <= 5; i++) {
		roomButtonClips.push_back({ 16, 0, 16, 16 });
	}

	for (int i = 6; i <= 8; i++) {
		roomButtonClips.push_back({ 32, 0, 16, 16 });
	}
}

//handle all menu rendering based on whether on select screen or not
void Menu::renderMenu(KMPlayerCharacter &husk) {

	if (menu) {
		if (!selectScreen) {

			for (int i = 0; i <= QUIT; i++) {
				menuButtonsTexture.render(menuButtons[i].getButtonRect().x, menuButtons[i].getButtonRect().y, &menuButtonClips[i]);
			}
			//-1 for start, -2 for select, -3 for quit
			//render string highlight rect
			if (stringHighlight == -1) { highlightRect = { 92, 8, 72, 30 }; }
			else if (stringHighlight == -2) { highlightRect = { 92, 52, 72, 30 }; }
			else if (stringHighlight == -3) { highlightRect = { 92, 99, 72, 30 }; }
			stringHighlightTexture.render(highlightRect.x, highlightRect.y);

		}
		//else if select screen
		else {

			//render highlight
			if (intHighlight > maxRoom) { intHighlight = maxRoom; }
			intHighlightTexture.render(roomButtons[intHighlight].getButtonRect().x - 2, roomButtons[intHighlight].getButtonRect().y - 2);

			//probelm caused below this
			//render buttons
			for (int i = 0; i <= maxRoom; i++) {

				roomButtonsTexture.render(roomButtons[i].getButtonRect().x, roomButtons[i].getButtonRect().y, &roomButtonClips[i]);	
				
			}
		
		}

	}
}	


bool Menu::loadMenuTextures(KMPlayerCharacter &husk) {
	bool success = true;


	if (!menuButtonsTexture.loadFromImage("sprites/mm/menuButtons.png")) {
		std::cout << "Failed to load menu buttons texture!\n";
		success = false;
	}

	if (!stringHighlightTexture.loadFromImage("sprites/mm/stringHighlight.png")) {
		std::cout << "Failed to load string highlight texture!\n";
	}

	if (!roomButtonsTexture.loadFromImage("sprites/mm/roomButton.png")) {
		std::cout << "Failed to load room buttons texture!";
	}


	if (!intHighlightTexture.loadFromImage("sprites/mm/intHighlight.png")) {
		std::cout << "Failed to load int highlights texture!";
	}

	return success;

}

void Menu::freeMenuTextures() {

	menuButtonsTexture.free();
	stringHighlightTexture.free();
	roomButtonsTexture.free();
	intHighlightTexture.free();

}


void Menu::handleMenuEvents(SDL_Event& e, bool& quit, KMWindow& window, SDL_Renderer* kmRenderer) {

	//if in menu
	if (menu) {

		while (SDL_PollEvent(&e) != 0) {

			if (e.type == SDL_QUIT) {
				menu = false;
				started = false;
				quit = true;
				break;
			}

			window.handleEvents(e, kmRenderer, quit);
			
			//if a key is pressed
			if (e.type == SDL_KEYDOWN && (!(SDL_GetModState() & KMOD_ALT))) {
		
				//if not on select screen
				if (!selectScreen) {
					
					//if up pressed
					if (e.key.keysym.sym == SDLK_UP && e.key.repeat == 0) {
						if (stringHighlight == -2) { stringHighlight = -1; }
						else if (stringHighlight == -3) { stringHighlight = -2; }
					}

					//if down pressed
					else if (e.key.keysym.sym == SDLK_DOWN && e.key.repeat == 0) {
						if (stringHighlight == -2) { stringHighlight = -3; }
						else if (stringHighlight == -1) { stringHighlight = -2; }
					}
					//if return pressed
					else if (e.key.keysym.sym == SDLK_RETURN && e.key.repeat == 0) {

						if (stringHighlight == -1) {
							menu = false;
							started = true;
							room = maxRoom + 1;
						}
						
						else if (stringHighlight == -2) {
							selectScreen = true;
						}

						//if quit
						else if (stringHighlight == -3) {
							menu = false;
							started = false;
							quit = true;
						}

					}

				}

				//if on select screen
				else if (selectScreen) {
					
					if (intHighlight > maxRoom) { intHighlight = maxRoom - 1; }

					if (e.key.keysym.sym == SDLK_ESCAPE) {
						selectScreen = false;
					}


					//if arrow keys pressed
					if (e.key.keysym.sym == SDLK_RIGHT) {
						if (intHighlight < maxRoom && intHighlight!= 2 && intHighlight != 5) { intHighlight += 1; }
					}
					else if (e.key.keysym.sym == SDLK_LEFT) {
						if (intHighlight > 0 && intHighlight != 3 && intHighlight != 6) { intHighlight -= 1; }
					}
					else if (e.key.keysym.sym == SDLK_UP) {
						if (intHighlight - 3 >= 0) { intHighlight -= 3; }
					}
					else if (e.key.keysym.sym == SDLK_DOWN) {
						if (intHighlight + 3 <= maxRoom) { intHighlight += 3; }
					}
					else if (e.key.keysym.sym == SDLK_RETURN) {
						room = intHighlight + 1;
						selectScreen = false;
						menu = false;
						started = true;
					}
				}
			}
		}
	}
	

}



//load max room
void Menu::loadMaxRoom() {
	std::ifstream dataFile("files/rooms/roomM.aog");

	if (!dataFile.is_open()) { std::cout << "Failed to load max room reached!"; }
	else {	dataFile >> maxRoom; }
	dataFile.close();

}

void Menu::updateRoomButtons() {
	roomButtons.clear();

	int i = 0;
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {

			if (i <= maxRoom) {
				
				roomButtons.push_back(MButton(80 + col * 32, 16 + row * 32, 16, 16, i));
				i++;
			}
			else { break; }

		}
	}

}



bool Menu::onSelectScreen() { return selectScreen; }
bool Menu::inMenu() { return menu; }
bool Menu::isStarted(){ return started; }
void Menu::setMenu(bool menuStatus) { menu = menuStatus; }
void Menu::setMaxRoom(int eMaxRoom) { maxRoom = eMaxRoom; }