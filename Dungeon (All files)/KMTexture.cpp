#include"KMTexture.h"

#include<SDL_image.h>

KMTexture::KMTexture() {

	kmTexture = NULL;
	TEXTURE_WIDTH = 0;
	TEXTURE_HEIGHT = 0;
}

KMTexture::~KMTexture() {
	free();
}

void KMTexture::free() {
	if (kmTexture != NULL) {
		SDL_DestroyTexture(kmTexture);
		kmTexture = NULL;
		TEXTURE_WIDTH = 0;
		TEXTURE_HEIGHT = 0;
	}
}


//Render texture or clip
void KMTexture::render(int x, int y, SDL_Rect* clip, int rotation, SDL_Point* centre, SDL_RendererFlip flip) {

	//rect to render to
	SDL_Rect targetRect = { 0,0,0,0 };
	targetRect.x = x;
	targetRect.y = y;
	targetRect.w = TEXTURE_WIDTH;
	targetRect.h = TEXTURE_HEIGHT;

	//if clip present, set target rect
	if (clip != NULL) {
		targetRect.w = clip->w;
		targetRect.h = clip->h;
	}

	SDL_RenderCopyEx(kmRenderer, kmTexture, clip, &targetRect, rotation, centre, flip);

}

//Load image
bool KMTexture::loadFromImage(std::string path) {

	//success boolean
	bool success = true;

	SDL_Surface* tempSurface = NULL;
	tempSurface = IMG_Load(path.c_str());

	if (tempSurface == NULL) {
		std::cout << "Failed to load temp surface! IMG_Error: " << IMG_GetError();
		success = false;
	}

	//If temp surface loaded successfully
	else {

		//grab dimensions
		TEXTURE_WIDTH = tempSurface->w;
		TEXTURE_HEIGHT = tempSurface->h;

		//set color key
		SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 0x00, 0xFF, 0xFF));

		//Create texture
		kmTexture = SDL_CreateTextureFromSurface(kmRenderer, tempSurface);

		//if failed to create texture
		if (kmTexture == NULL) {
			std::cout << "Failed to create texture form surface! SDL Error: " << SDL_GetError();
			success = false;
		}

	}

	SDL_FreeSurface(tempSurface);

	return success;
}


void KMTexture::setAlpha(int a) {
	SDL_SetTextureAlphaMod(kmTexture, a);
}


int KMTexture::getTextureWidth() { return TEXTURE_WIDTH; }
int KMTexture::getTextureHeight() { return TEXTURE_HEIGHT; }
bool KMTexture::isTextureLoaded() { return kmTexture != NULL; }
