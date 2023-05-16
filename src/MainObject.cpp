#include "MainObject.h"

MainObject::MainObject()
{
    status_ = STAND;
    frame = 0;
    x_pos = TILE_SIZE;
    y_pos = 0;
    x_val = 0;
    y_val = 0;
    width_frame = 0;
    height_frame = 0;

    camera_x = 0;
    camera_y = 0;

    is_win = false;
}

MainObject::~MainObject()
{
}

bool MainObject::LoadImg(std::string path, SDL_Renderer *screen)
{
    bool ret = Texture::LoadImg(path, screen);
    if (ret == true)
    {
        width_frame = 20;
        height_frame = rect.h;
    }
    return ret;
}

void MainObject::set_clip()
{

    if (width_frame > 0 && height_frame > 0)
    {
        for (int i = 0; i < 4; i++)
        {
            frame_clip[0].x = 6;
            frame_clip[0].y = 0;
            frame_clip[0].w = width_frame;
            frame_clip[0].h = height_frame;

            frame_clip[1].x = 38;
            frame_clip[1].y = 0;
            frame_clip[1].w = width_frame;
            frame_clip[1].h = height_frame;

            frame_clip[2].x = 70;
            frame_clip[2].y = 0;
            frame_clip[2].w = width_frame;
            frame_clip[2].h = height_frame;

            frame_clip[3].x = 102;
            frame_clip[3].y = 0;
            frame_clip[3].w = width_frame;
            frame_clip[3].h = height_frame;
        }
    }
}

void MainObject::show(SDL_Renderer *des)
{
    if (direction_ == UP)
    {
        LoadImg("image/character/ball_up.png", des);
    }
    if (direction_ == DOWN)
    {
        LoadImg("image/character/ball_down.png", des);
    }
    if (direction_ == LEFT)
    {
        LoadImg("image/character/ball_left.png", des);
    }
    else if (direction_ == RIGHT)
        LoadImg("image/character/ball_right.png", des);

    if (status_ == WALK)
    {
        frame++;
        if (frame > 3)
            frame = 0;
    }
    else
        frame = 0;

    rect.x = x_pos - camera_x;
    rect.y = y_pos - camera_y;

    SDL_Rect *current_clip = &frame_clip[frame];
    SDL_Rect renderQuad = {rect.x, rect.y, width_frame, height_frame};

    SDL_RenderCopy(des, p_object, current_clip, &renderQuad);
}

void MainObject::HandleEvent(SDL_Event events, SDL_Renderer *screen)
{
    if (events.type == SDL_KEYDOWN)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_UP:
        {
            status_ = WALK;
            direction_ = UP;
            y_val -= BALL_VEL;
        }
        break;

        case SDLK_DOWN:
        {
            status_ = WALK;
            direction_ = DOWN;
            y_val += BALL_VEL;
        }
        break;

        case SDLK_LEFT:
        {
            status_ = WALK;
            direction_ = LEFT;
            x_val -= BALL_VEL;
        }
        break;

        case SDLK_RIGHT:
        {
            status_ = WALK;
            direction_ = RIGHT;
            x_val += BALL_VEL;
        }
        break;

        default:
            break;
        }
    }
    else if (events.type == SDL_KEYUP)
    {
        status_ = STAND;
        switch (events.key.keysym.sym)
        {
        case SDLK_UP:
            y_val += BALL_VEL;
            break;
        case SDLK_DOWN:
            y_val -= BALL_VEL;
            break;
        case SDLK_LEFT:
            x_val += BALL_VEL;
            break;
        case SDLK_RIGHT:
            x_val -= BALL_VEL;
            break;
        }
    }
}

void MainObject::move(Map& map_data)
{
    x_val = 0;
    y_val = 0;

    if(status_ == WALK && direction_ == UP)
    {
        y_val -= BALL_VEL;
    }
    if(status_ == WALK && direction_ == DOWN)
    {
        y_val += BALL_VEL;
    }
    if(status_ == WALK && direction_ == LEFT)
    {
        x_val -= BALL_VEL;
    }
    if(status_ == WALK && direction_ == RIGHT)
    {
        x_val += BALL_VEL;
    }
    
    check_map(map_data);
    SetCamera(map_data);
}

void MainObject::check_map(Map& map_data)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    int height_min = height_frame < TILE_SIZE ? height_frame : TILE_SIZE;
    x1 = (x_pos + x_val)/TILE_SIZE;
    x2 = (x_pos + x_val + width_frame - 1)/TILE_SIZE;

    y1 = y_pos / TILE_SIZE;
    y2 = (y_pos + height_frame - 1)/TILE_SIZE;

    if(x1 >= 0 && x2 < LEVEL_WIDTH && y1 >= 0 && y2 < LEVEL_HEIGHT)
    {
        if(x_val > 0)
        {
            if(map_data.tile[y1][x2] == 1 || map_data.tile[y2][x2] == 1)
            {
                x_pos = x2*TILE_SIZE;
                x_pos -= width_frame + 1;
                x_val = 0;
            }
            if(map_data.tile[y1][x2] == 2 || map_data.tile[y2][x2] == 2)
            {
                is_win = true;
            }
        }
        if(x_val < 0)
        {
            if(map_data.tile[y1][x1] == 1 || map_data.tile[y2][x1] == 1)
            {
                x_pos = (x1 + 1)*TILE_SIZE;
                x_val = 0;
            }
            if(map_data.tile[y1][x1] == 2 || map_data.tile[y2][x1] == 2)
            {
                is_win = true;
            }
        }
    }

    int width_min = width_frame < TILE_SIZE ? width_frame : TILE_SIZE;
    x1 = x_pos/TILE_SIZE;
    x2 = (x_pos + width_frame)/TILE_SIZE;

    y1 = (y_pos + y_val)/TILE_SIZE;
    y2 = (y_pos + y_val + height_frame - 1)/TILE_SIZE;

    if(x1 >= 0 && x2 < LEVEL_WIDTH && y1 >= 0 && y2 < LEVEL_HEIGHT)
    {
        if(y_val > 0)
        {
            if(map_data.tile[y2][x1] == 1 || map_data.tile[y2][x2] == 1)
            {
                y_pos = y2*TILE_SIZE;
                y_pos -= height_frame + 1;
                y_val = 0;
            }
            if(map_data.tile[y2][x1] == 2 || map_data.tile[y2][x2] == 2)
            {
                is_win = true;
            }
        }

        if(y_val < 0)
        {
            if(map_data.tile[y1][x1] == 1 || map_data.tile[y1][x2] == 1)
            {
                y_pos = (y1 + 1)*TILE_SIZE;
                y_val = 0;
            }
            if(map_data.tile[y1][x1] == 2 || map_data.tile[y1][x2] == 2)
            {
                is_win = true;
            }
        }
    }

    x_pos += x_val;
    y_pos += y_val;

    if( x_pos < 0)
    {
        x_pos = 0;
    }
    else if( x_pos + width_frame > LEVEL_WIDTH)
    {
        x_pos -= x_val;
    }

    if( y_pos < 0)
    {
        y_pos = 0;
    }
    else if( y_pos + height_frame > LEVEL_HEIGHT)
    {
        y_pos -= y_val;
    }

}

void MainObject::SetCamera(Map& map_data)
{
    map_data.start_x = x_pos - SCREEN_WIDTH/2;
    if(map_data.start_x < 0)
    {
        map_data.start_x = 0;
    }
    else if(map_data.start_x + SCREEN_WIDTH >= LEVEL_WIDTH)
    {
        map_data.start_x = LEVEL_WIDTH - SCREEN_WIDTH;
    }

    map_data.start_y = y_pos -SCREEN_HEIGHT/2;
    if(map_data.start_y < 0)
    {
        map_data.start_y = 0;
    }
    else if(map_data.start_y + SCREEN_HEIGHT >= LEVEL_HEIGHT)
    {
        map_data.start_y = LEVEL_HEIGHT - SCREEN_HEIGHT;
    }
}

bool MainObject::is_walk()
{
    return status_ != STAND;
}

bool MainObject::win()
{
    return is_win != false;
}