#ifndef MAIN_PLAYER_H
#define MAIN_PLAYER_H

#include"base.h"
#include"BaseObject.h"

# define FRAME_NUM 8
# define GRAVITY_SPEED 0.8
# define MAX_FALL_SPEED 10
# define PLAYER_SPEED 8
# define PLAYER_JUMP_VALUE 18

class MainPlayer : public BaseObject 
{
public:
    MainPlayer();
    ~MainPlayer();

    enum WalkType{
        WALK_RIGHT = 0,
        WALK_LEFT = 1
    };

    // load 8-frame-picture and take value of width frame and height frame
    bool LoadImg(std::string path, SDL_Renderer* screen);

    /*
    based on status to render approriate image(left or right) on renderer
    based on key action to increase frame to choose appropriate frame -> smooth movement
    decide coordinate of player based on current position and new mapX, mapY
    */
    void Show(SDL_Renderer* des);

    // base on key press action to modify 'inputType' : hold ongoing key press
    void HandleInput(SDL_Event events, SDL_Renderer* screen);
    
    // create info about frame-rect on big picture
    void SetClips();

    void DoPlayer(Map& mapData);

    /*
    handle interaction between player and map in 4 directions
    */
    void CheckToMap(Map& mapData);

    /* base on current position of player to decide where new map locate
    modify mapData.startX, mapData.startY
    */
    void CenterEntityOnMap(Map& mapData);

    // use to assign new start coordinate of map to mapX, mapY
    void SetMapXY(const int mapX, const int mapY) { this -> mapX = mapX; this -> mapY = mapY; };
private:
    float xVal;
    float yVal;

    float xPos;
    float yPos;

    int widthFrame;
    int heightFrame;

    SDL_Rect frameCLip[FRAME_NUM];
    Input inputType;
    int frame;
    int status;

    bool onGround;

    // hold coordinate of place starting new map
    int mapX;
    int mapY;

    int comeBackTime;
};

#endif