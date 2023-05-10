#include "Text.h"

Text::Text()
{
    text_color.r = 0xFF;
    text_color.g = 0xFF;
    text_color.b = 0xFF;
    texture = NULL;
}

Text::~Text()
{

}

bool Text::LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen)
{
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, str_.c_str(), text_color);
    if(text_surface)
    {
        texture = SDL_CreateTextureFromSurface(screen, text_surface);
        width = text_surface->w;
        height = text_surface->h;

        SDL_FreeSurface(text_surface);
    }
    return texture != NULL;
}

void Text::Free()
{
    if(texture != NULL)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}

void Text::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
    text_color.r = red;
    text_color.g = green;
    text_color.b = blue;
}

void Text::SetColor(int type)
{
    if(type == RED_TEXT)
    {
        SDL_Color color_ = {0xFF, 0x00, 0x00};
        text_color = color_;
    }
    else if(type == WHITE_TEXT)
    {
        SDL_Color color_ = {0xFF, 0xFF, 0xFF};
        text_color = color_;
    }
    else if(type == BLACK_TEXT)
    {
        SDL_Color color_ = {0x00, 0x00, 0x00};
        text_color = color_;
    }
}

void Text::RenderText(SDL_Renderer* screen,
                      int xp, int yp, 
                      SDL_Rect* clip, 
                      double angle, 
                      SDL_Point* center, 
                      SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = {xp, yp, width, height};
    if(clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx(screen, texture, clip, &renderQuad, angle, center, flip);
}