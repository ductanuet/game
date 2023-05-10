#ifndef TEXT_H_
#define TEXT_H_

#include "commonFunction.h"
#include "Texture.h"

class Text : public Texture
{
public:
    enum TextColor
    {
        RED_TEXT = 0,
        WHITE_TEXT = 1,
        BLACK_TEXT = 2
    };

    Text();
    ~Text();
    void SetText(const std::string text) {str_ = text;};
    void SetColor(const int& type);
    void CreateText(TTF_Font* font, SDL_Renderer* des);

private:
    std::string str_;
    SDL_Color text_color;
};

#endif