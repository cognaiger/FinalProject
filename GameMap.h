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

// class that represent main map of the game
class GameMap {
public: 
    GameMap() {;}
    ~GameMap() {;}

    // load text-map into gameMap (chunk of info) and find maxX, maxY of map
    void LoadMap(char* path);

    // load image of each tile into 'tileMat'
    void LoadTiles(SDL_Renderer* screen);

    /*
    base on startX and startY of map to decide range of map
    for each value on map, draw corresponding tile
    */
    void DrawMap(SDL_Renderer* screen);

    // return gameMap (chunk of info)
    Map GetMap() const { return gameMap; }

    // assign 'gameMap' by argument
    void SetMap(Map& mapData) { gameMap = mapData; };
private:
    // chunk of info: start coordinates, max x-pos, y-pos of map, path to file text-map
    Map gameMap;

    // each tileMat represent 1 tile image
    TileMat tileMat[MAX_TILES];
};

#endif