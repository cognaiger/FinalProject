#ifndef THREAT_OBJECT_H
#define THREAT_OBJECT_H

#include"base.h"
#include"BaseObject.h"
#include"BulletObject.h"

#define THREAT_FRAME_NUM 8
#define THREAT_MAX_FALL_SPEED 10
#define THREAT_SPEED 3

class ThreatObject : public BaseObject
{
public:
    ThreatObject();
    ~ThreatObject();

    enum TypeMove {
        STATIC_THREAT = 0,
        MOVE_IN_SPACE_THREAT = 1
    };

    void SetXVal(const float& xVal_) { xVal = xVal_; }
    void SetYVal(const float& yVal_) { yVal = yVal_; } 

    void SetXPos(const float& xp) { xPos = xp; }
    void SetYPos(const float& yp) { yPos = yp; }
    float GetXPos() const { return xPos; }
    float GetYPos() const { return yPos; }

    void SetMapXY(const int& mx, const int& my) { mapX = mx; mapY = my; }

    void InitThreat();

    void SetClips();
    bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);

    int GetWidthFrame() const { return widthFrame; }
    int GetHeightFrame() const { return heightFrame; }

    void DoThreat(Map& mapData);
    void CheckToMap(Map& mapData);

    void SetTypeMove(const int& typeMove_) { typeMove = typeMove_; }
    void SetAnimationPos(const int& posA, const int& posB) { animationA = posA; animationB = posB; }
    void SetInputLeft(const int& ipLeft) { inputType.left = ipLeft; }
    void ImpMoveType(SDL_Renderer* screen);

    std::vector<BulletObject*> GetBulletList() const { return bulletList; }
    void SetBulletList(const std::vector<BulletObject*>& bulletList_) { bulletList = bulletList_; }

    void InitBullet(BulletObject* pBullet, SDL_Renderer* screen);
    void MakeBullet(SDL_Renderer* screen, const int& xLimit, const int& yLimit);

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

    int typeMove;
    int animationA;
    int animationB;

    Input inputType;

    std::vector<BulletObject*> bulletList;
};

#endif