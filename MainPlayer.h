#ifndef MAIN_PLAYER_H
#define MAIN_PLAYER_H

#include<vector>
#include"base.h"
#include"BaseObject.h"
#include"BulletObject.h"

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
        WALK_NONE = 0,
        WALK_RIGHT = 1,
        WALK_LEFT = 2
    };

    // load 8-frame-picture and take value of width frame and height frame
    bool LoadImg(std::string path, SDL_Renderer* screen);

    /*
    based on status to render approriate image(left or right) on renderer
    based on key action to increase frame to choose appropriate frame -> smooth movement
    decide coordinate of player based on current position and new mapX, mapY
    */
    void Show(SDL_Renderer* des);

    // base on key press action to modify 'inputType' and 'status'
    void HandleInput(SDL_Event events, SDL_Renderer* screen);
    
    // create info about frame-rect on big picture
    void SetClips();

    /* 
    handle distance player will move vertically and horizonally (xVal, yVal)
    based on current input
    */
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

    // base on current status (right, left, jump) to decide which spirit-image to load 
    // (utility func)
    void UpdateImagePlayer(SDL_Renderer* des);

    SDL_Rect GetRectFrame();

    void SetBulletList(std::vector<BulletObject*> bulletList) { pBulletList = bulletList; }

    std::vector<BulletObject*> GetBulletList() const { return pBulletList; }

    void HandleBullet(SDL_Renderer* des);

    void RemoveBullet(const int& idx);

    void IncreaseCoin();
private:
    int coinCount;

    std::vector<BulletObject*> pBulletList;

    // distance player will move horizontally
    float xVal;
    // distance player will move vertically
    float yVal;

    // hold horizontal position
    float xPos;
    // hold vertical position
    float yPos;

    int widthFrame;
    int heightFrame;

    SDL_Rect frameCLip[FRAME_NUM];

    // hold input action
    Input inputType;

    // hold info about current frame of spirit picture
    int frame;

    // show player is runing left or right
    int status;

    bool onGround;

    // hold coordinate of place starting new map
    int mapX;
    int mapY;

    int comeBackTime;
};

#endif