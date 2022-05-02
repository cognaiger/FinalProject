#ifndef MAIN_PLAYER_H
#define MAIN_PLAYER_H

#include"base.h"
#include"BaseObject.h"

# define FRAME_NUM 8
# define GRAVITY_SPEED 0.8
# define MAX_FALL_SPEED 10
# define PLAYER_SPEED 8

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
    */
    void Show(SDL_Renderer* des);
    void HandleInput(SDL_Event events, SDL_Renderer* screen);
    
    // create info about frame-rect
    void SetClips();

    void DoPlayer(Map& mapData);
    void CheckToMap(Map& mapData);

    /* base on current position of player to decide where new map locate
    modify mapData.startX, mapData.startY
    */
    void CenterEntityOnMap(Map& mapData);

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

    int mapX;
    int mapY;
};

#endif