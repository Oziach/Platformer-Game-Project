#pragma once
#include<iostream>
#include<SDL.h>

class MButton {

private:
	int xPos;
	int yPos;
	int buttonWidth;
	int buttonHeight;
	SDL_Rect buttonRect;

	std::string stringButtonType;
	int intButtonType;

public:
	MButton(int x, int y, int w, int h, std::string type);
	MButton(int x, int y, int w, int h, int type);

	SDL_Rect& getButtonRect();
	bool getButtonPressed(SDL_Event& e, std::string stringHighlight, int intHighlight);

	int getIntButtonType() { return intButtonType; }
	std::string getStringButtonType() { return stringButtonType; }



	enum menuButtons {
		START, //0
		SELECT, //1
		QUIT //2

	};

};

