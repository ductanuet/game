#include "commonFunction.h"
#include "Texture.h"
#include "map.h"
#include "MainObject.h"
#include "Time.h"
#include "Text.h"
#include "Button.h"

enum gameStateEnum
{
    MENU = 0,
    PLAY = 1,
    HELP = 2,
    WIN = 3,
    LOSE = 4,
    END = 5
};

int gameState = MENU;

Texture background;
Texture menuground;
Texture win_game;
Texture game_over;

TTF_Font *gFont = NULL;

// music game
Mix_Music *gMusic = NULL;
// music menu
Mix_Music *gMenu = NULL;
// sound win
Mix_Music *gWin = NULL;
// sound lose
Mix_Music *gLose = NULL;

// time
Time fps_time;

bool init()
{
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!");
        }

        // Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Create vsynced renderer for window
            gscreen = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gscreen == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                // Initialize renderer color
                SDL_SetRenderDrawColor(gscreen, 0xFF, 0xFF, 0xFF, 0xFF);

                // Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }

                // Initialize SDL_mixer
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                {
                    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
                    success = false;
                }
                if (TTF_Init() == -1)
                {
                    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

bool LoadMedia()
{
    bool success = true;

    gMusic = Mix_LoadMUS("sound/sound_game.wav");
    if (gMusic == NULL)
    {
        printf("Failed to load game music! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    gMenu = Mix_LoadMUS("sound/sound_menu.wav");
    if (gMenu == NULL)
    {
        printf("Failed to load menu music! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    gWin = Mix_LoadMUS("sound/win_sound.wav");
    if (gWin == NULL)
    {
        printf("Failed to load win music! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    gLose = Mix_LoadMUS("sound/game_over.wav");
    if (gLose == NULL)
    {
        printf("Failed to load game over music! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }

    else
    {
        gFont = TTF_OpenFont("font/KarmaFuture.ttf", 20);
        if (gFont == NULL)
        {
            printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
            success = false;
        }
        else
        {
            if (!win_game.LoadImg("image/screen/win_game.png", gscreen))
            {
                printf("Failed to load win game image\n");
                success = false;
            }
            if (!game_over.LoadImg("image/screen/game_over1.png", gscreen))
            {
                printf("Failed to load game over image\n");
                success = false;
            }
        }
    }

    return success;
}

void close()
{
    // background.Free();

    SDL_DestroyRenderer(gscreen);
    gscreen = NULL;

    Mix_FreeMusic(gMenu);
    gMenu = NULL;

    Mix_FreeMusic(gMusic);
    gMusic = NULL;

    Mix_FreeMusic(gWin);
    gWin == NULL;

    Mix_FreeMusic(gLose);
    gLose == NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

void game()
{
    // Mix_PlayMusic( gMusic, 6 );

    Time game_time;

    GameMap game_map_;
    game_map_.LoadMap("map/maze1.txt");
    game_map_.LoadTiles(gscreen);

    MainObject ball;
    ball.LoadImg("image/character/ball_down.png", gscreen);
    ball.LoadImg("image/character/ball_up.png", gscreen);
    ball.LoadImg("image/character/ball_left.png", gscreen);
    ball.LoadImg("image/character/ball_right.png", gscreen);

    ball.set_clip();

    // time text
    Text time_game;
    game_time.start();
    time_game.SetColor(Text::WHITE_TEXT);

    bool is_quit = false;
    Mix_PlayMusic(gMusic, -1);

    while (!is_quit)
    {

        fps_time.start();
        while (SDL_PollEvent(&gEvent) != 0)
        {
            if (gEvent.type == SDL_QUIT)
            {
                gameState = END;
                is_quit = true;
            }

            ball.HandleEvent(gEvent, gscreen);
        }

        SDL_SetRenderDrawColor(gscreen, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(gscreen);

        if (ball.win() == true)
        {
            Mix_HaltMusic();
            gameState = WIN;
            is_quit = true;
        }
        else
        {

            background.Render(gscreen, NULL);

            game_map_.DrawMap(gscreen);
            Map map_data = game_map_.getMap();

            ball.SetMapXY(map_data.start_x, map_data.start_y);
            ball.move(map_data);
            ball.show(gscreen);

            game_map_.SetMap(map_data);

            // show game's time
            std::string str_time = "Time: ";

            int time_val = game_time.get_ticks() / 1000;
            int val_time = 360 - time_val;
            if (val_time <= 0)
            {
                Mix_HaltMusic();
                gameState = LOSE;
                is_quit = true;
            }
            else
            {
                std::string str_val = std::to_string(val_time);
                str_time += str_val;

                time_game.SetText(str_time);
                time_game.LoadFromRenderText(gFont, gscreen);
                time_game.RenderText(gscreen, SCREEN_WIDTH - 550, 30);
            }

            SDL_RenderPresent(gscreen);

            int real_time = fps_time.get_ticks();
            int time_one_frame = 1000 / FRAME_PER_SECOND;
            if (real_time < time_one_frame)
            {
                int delay_time = time_one_frame - real_time;
                SDL_Delay(delay_time);
            }

            if (gameState != PLAY)
            {
                is_quit = true;
            }
        }
    }
}

void win()
{
    bool is_quit = false;
    Mix_PlayMusic(gLose, -1);

    while (!is_quit)
    {

        fps_time.start();
        while (SDL_PollEvent(&gEvent) != 0)
        {
            if (gEvent.type == SDL_QUIT)
            {
                gameState = END;
                is_quit = true;
            }
        }

        SDL_SetRenderDrawColor(gscreen, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(gscreen);

        win_game.Render(gscreen, NULL);
        SDL_RenderPresent(gscreen);

        int real_time = fps_time.get_ticks();
        int time_one_frame = 1000 / FRAME_PER_SECOND;
        if (real_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_time;
            SDL_Delay(delay_time);
        }

        if (gameState != WIN)
        {
            is_quit = true;
        }
    }
}

void lose()
{
    bool is_quit = false;
    Mix_PlayMusic(gLose, -1);

    
    while (!is_quit)
    {

        fps_time.start();
        while (SDL_PollEvent(&gEvent) != 0)
        {
            if (gEvent.type == SDL_QUIT)
            {
                gameState = END;
                is_quit = true;
            }

            if (gEvent.type == SDL_KEYDOWN && gEvent.key.keysym.sym == SDLK_SPACE)
            {
                gameState = PLAY;
                is_quit = true;
            }
        }

        SDL_SetRenderDrawColor(gscreen, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(gscreen);

        game_over.Render(gscreen, NULL);

        Text lose;
        lose.SetColor(Text::WHITE_TEXT);
        std::string str_lose = "Press the ""space"" button to play again or the ""esc"" button to exit the game";
        lose.SetText(str_lose);
        lose.LoadFromRenderText(gFont, gscreen);
        lose.RenderText(gscreen, SCREEN_WIDTH - 870, 700);

        SDL_RenderPresent(gscreen);

        int real_time = fps_time.get_ticks();
        int time_one_frame = 1000 / FRAME_PER_SECOND;
        if (real_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_time;
            SDL_Delay(delay_time);
        }

        if (gameState != LOSE)
        {
            is_quit = true;
        }
    }
}


void menu()
{
    Button startButton, quitButton;
    Mix_PlayMusic(gMenu, -1);

    menuground.LoadImg("image/screen/menu.png", gscreen);
    startButton.setPosition(346, 288, 308, 87);

    quitButton.setPosition(346, 610, 308, 87);

    bool is_quit = false;
    while (!is_quit)
    {
        // fps_time.start();

        while (SDL_PollEvent(&gEvent) != 0)
        {
            if (gEvent.type == SDL_QUIT)
            {
                gameState = END;
                is_quit = true;
            }

            startButton.handleEvent(&gEvent);

            quitButton.handleEvent(&gEvent);

            if (startButton.getCurrentSprite() == Button::BUTTON_SPRITE_MOUSE_DOWN)
            {
                gameState = PLAY;
                is_quit = true;
            }

            if (quitButton.getCurrentSprite() == Button::BUTTON_SPRITE_MOUSE_DOWN)
            {
                gameState = END;
                is_quit = true;
            }
        }

        SDL_SetRenderDrawColor(gscreen, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(gscreen);

        menuground.Render(gscreen, NULL);
        startButton.render(gscreen);

        SDL_RenderPresent(gscreen);

        if (gameState != MENU)
        {
            is_quit = true;
        }
    }
}

void manageState()
{
    while (true)
    {
        if (gameState == MENU)
        {
            menu();
        }
        else if (gameState == PLAY)
        {
            game();
        }
        // else if (gameState == HELP)
        // {
        //     help();
        // }
        else if (gameState == WIN)
        {
            win();
        }
        else if (gameState == LOSE)
        {
            lose();
        }
        else if (gameState == END)
            break;
    }
}

int main(int argc, char *argv[])
{

    if (!init())
    {
        printf("Failed to initialize!\n");
        return 0;
    }
    // Load media
    if (!LoadMedia())
    {
        printf("Failed to load media!\n");
        return 0;
    }

    manageState();

    close();

    return 0;
}