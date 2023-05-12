#ifndef MAINOBJECT_H_
#define MAINOBJECT_H_

#include "commonFunction.h"
#include "Texture.h"

class MainObject : public Texture
{
public:

    enum Status
    {
        WALK,
        STAND
    };
    enum Direction
    {
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    MainObject();
    ~MainObject();

    bool LoadImg(std::string path, SDL_Renderer* screen);
    void show(SDL_Renderer* des);
    void HandleEvent(SDL_Event events, SDL_Renderer* screen);
    void set_clip();

    //di chuyen
    void move(Map& map_data);
    //check va cham
    void check_map(Map& map_data);

    void SetMapXY(const int map_x, const int map_y) {camera_x = map_x; camera_y = map_y;};
    void SetCamera(Map& map_data);
    //void UpdateImage(SDL_Renderer* des);
    bool is_walk();
    bool win();

private:
    //van toc theo truc Ox, Oy
    float x_val;
    float y_val;

    // vi tri hien tai
    float x_pos;
    float y_pos;

    //kich thuoc cua 1 frame
    int width_frame;
    int height_frame;

    SDL_Rect frame_clip[4];

    Status status_;
    Direction direction_;
    int frame;

    int camera_x;
    int camera_y;

    bool is_win;
     
};

#endif