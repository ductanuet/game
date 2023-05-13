// #ifndef BUTTON_H_
// #define BUTTON_H_

// #include "commonFunction.h"
// #include "Texture.h"

// class LButton
// {
// 	public:

//         enum LButtonSprite
//     {
// 	    BUTTON_SPRITE_MOUSE_OUT = 0,
// 	    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
// 	    BUTTON_SPRITE_MOUSE_DOWN = 2,
// 	    BUTTON_SPRITE_MOUSE_UP = 3,
// 	    BUTTON_SPRITE_TOTAL = 4
//     };
// 		//Initializes internal variables
// 		LButton();

// 		//Sets top left position
// 		void setPosition( int x, int y );

// 		//Handles mouse event
// 		void handleEvent( SDL_Event* e );
	
// 		//Shows button sprite
// 		void render();

// 	private:
// 		//Top left position
// 		SDL_Point mPosition;

// 		//Currently used global sprite
// 		LButtonSprite mCurrentSprite;
//         Texture gButtonSpriteSheetTexture;
//         SDL_Rect gSpriteClips;
// };

// #endif