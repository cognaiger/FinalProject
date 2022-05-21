#ifndef THREAT_OBJECT_H
#define THREAT_OBJECT_H

#include"base.h"
#include"BaseObject.h"
#include"BulletObject.h"
#include"GameMap.h"

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

    // recharge threat
    void InitThreat();

    // set clip of frames
    void SetClips();

    // load img and get widthFrame, heightFrame
    bool LoadImg(std::string path, SDL_Renderer* screen);
    bool LoadImgRight(SDL_Renderer* screen);
    bool LoadImgLeft(SDL_Renderer* screen);

    // base on frame to show threat (comebackTime = 0)
    void Show(SDL_Renderer* des);

    int GetWidthFrame() const { return widthFrame; }
    int GetHeightFrame() const { return heightFrame; }

    // handle distance threat will move horizontally and vertically
    void DoThreat(Map& mapData, SDL_Renderer* screen);

    // check interaction with map
    void CheckToMap(Map& mapData, SDL_Renderer* screen);

    void SetTypeMove(const int& typeMove_) { typeMove = typeMove_; }

    // set limit dynamic threat can move
    void SetAnimationPos(const int& posA, const int& posB) { animationA = posA; animationB = posB; }
    void SetInputLeft() { inputType.right = 0, inputType.left = 1; }
    void SetInputRight() { inputType.left = 0, inputType.right = 1; }
    
    // decide which direct threat move (limit pos, ...)
    void ImpMoveType(SDL_Renderer* screen);

    std::vector<BulletObject*> GetBulletList() const { return bulletList; }
    void SetBulletList(const std::vector<BulletObject*>& bulletList_) { bulletList = bulletList_; }

    // init bullet type, direct, start pos, velocity
    void InitBullet(BulletObject* pBullet, SDL_Renderer* screen);

    // base on bulletList to render bullet on screen
    void MakeBullet(SDL_Renderer* screen, const int& xLimit, const int& yLimit);

    // delete where pullet point to
    void RemoveBullet(const int& idx);
    SDL_Rect GetRectFrame();
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