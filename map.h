#ifndef MAP_H_
#define MAP_H_

#include "commonFunction.h"
#include "Texture.h"

const int MAX_TILE = 3;

class TileMap : public Texture
{
public:
    TileMap() {;}
    ~TileMap() {;}
};

class GameMap
{
public:
    GameMap() {;}
    ~GameMap() {;}

    void LoadMap(char* name);
    void LoadTiles(SDL_Renderer* screen);
    void DrawMap(SDL_Renderer* screen);
    //lấy dữ liệu map
    Map getMap() const {return game_map;};
    //
    void SetMap(Map& map_data) {game_map = map_data;};

private:
    Map game_map;
    TileMap tile_map[MAX_TILE];
};


#endif