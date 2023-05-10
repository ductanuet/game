#include "Text.h"

Text::Text()
{
    ;
}

Text::~Text()
{

}

// void Text::SetColor(const int& type)
// {
//     if(type == RED_TEXT)
//     {
//         SDL_Color color = {0xFF, 0x00, 0x00};
//         text_color = color;
//     }
//     else if(type = WHITE_TEXT)
//     {
//         SDL_Color color = {0xFF, 0xFF, 0xFF};
//     }
//     else
//     {
//         SDL_Color color = {0, 0, 0};
//         text_color = color;
//     }



void Text::CreateText(TTF_Font* font, SDL_Renderer* des)
{
    //p_object = TTF_RenderText_Solid(font, str_.c_str(), text_color);
    //Show(des);
}