#include "MButton.h"

//constructor
MButton::MButton(int x, int y, int w, int h, std::string type) {
	xPos = x;
	yPos = y;
	buttonWidth = w;
	buttonHeight = h;
	stringButtonType = type;

	buttonRect = { xPos, yPos, buttonWidth, buttonHeight };
}

MButton::MButton(int x, int y, int w, int h, int type) {
	xPos = x;
	yPos = y;
	buttonWidth = w;
	buttonHeight = h;
	intButtonType = type;

	buttonRect = { xPos, yPos, buttonWidth, buttonHeight };

}



bool MButton::getButtonPressed(SDL_Event& e, std::string stringHighlight, int intHighlight) {

	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
		
		//if highlight is equal to button and enter pressed, return true
		if (stringHighlight == stringButtonType) {
			return true;
		}
		else {
			return false;
		}
		
	}

	return false;
}


SDL_Rect& MButton::getButtonRect() { return buttonRect; }