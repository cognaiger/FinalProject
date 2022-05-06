#ifndef THREAT_OBJECT_H
#define THREAT_OBJECT_H

#include"base.h"
#include"BaseObject.h"

#define THREAT_FRAME_NUM 8
#define THREAT_MAX_FALL_SPEED 10

class ThreatObject : public BaseObject
{
public:
    ThreatObject();
    ~ThreatObject();

    void SetXVal(const float& xVal_) { xVal = xVal_; }
    void SetYVal(const float& yVal_) { yVal = yVal_; } 

    void SetXPos(const float& xp) { xPos = xp; }
    void SetYPos(const float& yp) { yPos = yp; }
    float GetXPos() const { return xPos; }
    float GetYPos() const { return yPos; }

    void SetMapXY(const int& mx, const int& my) { mapX = mx; mapY = my; }

    void SetClips();
    bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);

    int GetWidthFrame() const { return widthFrame; }
    int GetHeightFrame() const { return heightFrame; }

    void DoThreat(Map& mapData);
    void CheckToMap(Map& mapData);

private:
    // hold limit of map
    int mapX;
    int mapY;

    float xVal;
    float yVal;

    float xPos;
    float yPos;

    int comeBackTime;
    bool onGround;
    SDL_Rect frameClip[THREAT_FRAME_NUM];
    int widthFrame;
    int heightFrame;
    int frame;
};

#endif