#ifndef MAIN_PLAYER_H
#define MAIN_PLAYER_H

#include"base.h"
#include"BaseObject.h"

# define FRAME_NUM 8

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
    void Show(SDL_Renderer* des);
    void HandleInput(SDL_Event events, SDL_Renderer* screen);
    // create info about frame-rect
    void SetClips();

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

};

#endif