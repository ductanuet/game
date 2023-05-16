#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "commonFunction.h"

class Texture
{
public:
    Texture();
    ~Texture();

    void SetRect(const int& x, const int& y)
    {
        rect.x = x;
        rect.y = y;
    }
    SDL_Rect GetRect() const {return rect;}
    SDL_Texture* GetTexture() const {return p_object;}

    virtual bool LoadImg(std::string path, SDL_Renderer* screen);
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    void Free();
//private:
    SDL_Texture* p_object;
    SDL_Rect rect;
};

#endif