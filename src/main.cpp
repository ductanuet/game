#include "commonFunction.h"
#include "Texture.h"
#include "map.h"
#include "MainObject.h"
#include "Time.h"

Texture background;
bool init()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
        return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    gWindow = SDL_CreateWindow("game maze", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (gWindow == NULL)
        success = false;
    else
    {
        gscreen = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
        if (gscreen == NULL)
        {
            success = false;
        }
        else
        {
            SDL_SetRenderDrawColor(gscreen, 0xFF, 0xFF, 0xFF, 0xFF);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
            {
                success = false;
            }
        }
    }
    return success;
}

// bool loadBackground()
// {
//     bool ret = background.LoadImg("D:\\maze_game\\image\\end_game.png", gscreen);
//     if (ret == false)
//     {
//         return false;
//     }
//     return true;
// }

void close()
{
    background.Free();

    SDL_DestroyRenderer(gscreen);
    gscreen = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char *argv[])
{
    Time fps_time;
    if (init() == false)
        return -1;
    // if (loadBackground() == false)
    //     return -1;

    GameMap game_map_;
    game_map_.LoadMap("maze1.txt");
    game_map_.LoadTiles(gscreen);

    MainObject ball;
    ball.LoadImg("ball_down.png", gscreen);
    ball.LoadImg("ball_up.png", gscreen);
    ball.LoadImg("ball_left.png", gscreen);
    ball.LoadImg("ball_right.png", gscreen);

    ball.set_clip();

    bool is_quit = false;
    while (!is_quit)
    {
        fps_time.start();
        while (SDL_PollEvent(&gEvent) != 0)
        {
            if (gEvent.type == SDL_QUIT)
            {
                is_quit = true;
            }
            if(gEvent.type == SDL_KEYDOWN && gEvent.key.keysym.sym == SDLK_ESCAPE)
            {
                is_quit = true;
            }
            ball.HandleEvent(gEvent, gscreen);
        }
        
        SDL_SetRenderDrawColor(gscreen, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(gscreen);

        background.Render(gscreen, NULL);

        game_map_.DrawMap(gscreen);
        Map map_data = game_map_.getMap();

        ball.SetMapXY(map_data.start_x, map_data.start_y);
        ball.move(map_data);
        ball.show(gscreen);

        game_map_.SetMap(map_data);
        //game_map_.DrawMap(gscreen);

        SDL_RenderPresent(gscreen);
        int real_time = fps_time.get_ticks();
        int time_one_frame = 1000/FRAME_PER_SECOND;
        if( real_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_time;
            SDL_Delay( delay_time );
        }
    }
    close();
    return 0;
}