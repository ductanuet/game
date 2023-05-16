#include "Button.h"

Button::Button()
{
    mPosition.x = 0;
    mPosition.y = 0;

    mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void Button::setPosition(int x, int y, int w, int h)
{
    mPosition.x = x;
    mPosition.y = y;
    width = w;
    height = h;
}

void Button::handleEvent(SDL_Event *e)
{
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        // Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        // Check if mouse is in button
        bool inside = true;

        // Mouse is left of the button
        if (x < mPosition.x)
        {
            inside = false;
        }
        // Mouse is right of the button
        else if (x > mPosition.x + width)
        {
            inside = false;
        }
        // Mouse above the button
        else if (y < mPosition.y)
        {
            inside = false;
        }
        // Mouse below the button
        else if (y > mPosition.y + height)
        {
            inside = false;
        }

        // Mouse is outside button
        if (!inside)
        {
            mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        }
        // Mouse is inside button
        else
        {
            // Set mouse over sprite
            switch (e->type)
            {
            case SDL_MOUSEMOTION:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;

            case SDL_MOUSEBUTTONDOWN:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                break;

            case SDL_MOUSEBUTTONUP:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
                break;
            }
        }
    }
}

Button::ButtonSprite Button::getCurrentSprite()
{
    return mCurrentSprite;
}

void Button::render(SDL_Renderer *gRenderer)
{
    // Show current button sprite
    gButtonTexture.Render(gRenderer, NULL);
}