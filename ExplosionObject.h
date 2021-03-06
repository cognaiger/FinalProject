#ifndef EXPLOSION_OBJECT_H
#define EXPLOSION_OBJECT_H

#include "base.h"
#include "BaseObject.h"

#define NUM_FRAME_EX 8

class ExplosionObject : public BaseObject 
{
public:
    ExplosionObject();
    ~ExplosionObject();
    
    // set clip for frames
    void SetClip();
    void SetFrame(const int& fr) { frame = fr; }

    // load image and get widthFrame, heightFrame
    virtual bool LoadImg(std::string path, SDL_Renderer* screen);

    // show explosion on renderer
    void Show(SDL_Renderer* screen);
    int GetFrameWidth() const { return frameWidth; }
    int GetFrameHeight() const { return frameHeight; }

private:
    int frameWidth;
    int frameHeight;

    unsigned int frame;
    SDL_Rect frameClip[NUM_FRAME_EX];
};

#endif