#ifndef BUTTON_H_
#define BUTTON_H_

#include "commonFunction.h"
#include "Texture.h"

const int BUTTON_WIDTH = 308;
const int BUTTON_HEIGHT = 87;

class Button
{
public:
	enum ButtonSprite
	{
		BUTTON_SPRITE_MOUSE_OUT = 0,
		BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
		BUTTON_SPRITE_MOUSE_DOWN = 2,
		BUTTON_SPRITE_MOUSE_UP = 3,
		BUTTON_SPRITE_TOTAL = 4
	};
	// Initializes internal variables
	Button();

	// Sets top left position
	void setPosition(int x, int y, int w, int h);

	// Handles mouse event
	void handleEvent(SDL_Event *e);

	// Gets button sprite
	ButtonSprite getCurrentSprite();

	// Shows button sprite
	void render(SDL_Renderer *gRenderer);

private:
	// Top left position
	SDL_Point mPosition;
	int width, height;

	// Currently used global sprite
	Texture gButtonTexture;
	ButtonSprite mCurrentSprite;
};

#endif