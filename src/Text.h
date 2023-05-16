#ifndef TEXT_H_
#define TEXT_H_

#include "commonFunction.h"

class Text
{
public:
    Text();
    ~Text();

    enum TextColor
    {
        RED_TEXT = 0,
        WHITE_TEXT = 1,
        BLACK_TEXT = 2
    };

    //doc file text
    //bool LoadFromFile(sdt::string path);
    //doc font chu
    bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen);
    void Free();

    //truyen truc tiep gia tri mau
    void SetColor(Uint8 red, Uint8 green, Uint8 blue);
    //set theo mau co ban o enum
    void SetColor(int type);

    void RenderText(SDL_Renderer* screen,
                    int xp, int yp, 
                    SDL_Rect* clip = NULL, 
                    double angle = 0.0, 
                    SDL_Point* center = NULL, 
                    SDL_RendererFlip flip = SDL_FLIP_NONE);
    int GetWidth() const { return width;};
    int GetHeight() const { return height;};

    void SetText(const std::string& text) {str_ = text;};
    std::string GetText() const { return str_;};

private:
    std::string str_;
    SDL_Color text_color;

    //quan ly text 
    SDL_Texture* texture;

    int width;
    int height;
};

#endif