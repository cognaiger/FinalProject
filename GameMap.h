#ifndef GAMEMAP_H
#define GAMEMAP_H

#include"base.h"
#include"BaseObject.h"

#define MAX_TILES 20

// class that represent tile of map 
class TileMat : public BaseObject
{
public:
    TileMat() {;}
    ~TileMat() {;}
};

// class that handle loading map
class GameMap {
public: 
    GameMap() {;}
    ~GameMap() {;}

    void LoadMap(char* path);
    // load tile image into 'tileMat'
    void LoadTiles(SDL_Renderer* screen);
    // for each value on map, draw corresponding tile
    void DrawMap(SDL_Renderer* screen);
private:
    Map gameMap;
    TileMat tileMat[MAX_TILES];

};

#endif