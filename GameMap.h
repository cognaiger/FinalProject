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

    // load text-map into gameMap
    void LoadMap(char* path);

    // load image of each tile into 'tileMat'
    void LoadTiles(SDL_Renderer* screen);

    /*
    base on startX and startY of map to decide range of map
    for each value on map, draw corresponding tile
    */
    void DrawMap(SDL_Renderer* screen);

    // return gameMap
    Map GetMap() const { return gameMap; }

    // assign 'gameMap' by argument
    void SetMap(Map& mapData) { gameMap = mapData; };
private:
    // contain info: start coordinates, max x-pos, y-pos of map, path to file text-map
    Map gameMap;

    // each tileMat represent 1 tile image
    TileMat tileMat[MAX_TILES];
};

#endif