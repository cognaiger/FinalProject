#ifndef BULLET_OBJECT_H
#define BULLET_OBJECT_H


#include"base.h"
#include"BaseObject.h"

// represent bullet that player shoot
class BulletObject : public BaseObject
{
public:
    BulletObject();
    ~BulletObject();

    enum BULLET_DIR {
        DIR_RIGHT = 20,
        DIR_LEFT = 21,
        DIR_UP = 22,
        DIR_UPLEFT = 23,
        DIR_UPRIGHT = 24,
        DIR_DOWN =25,
        DIR_DOWNRIGHT = 26,
        DIR_DOWNLEFT = 27
    };

    enum BulletType {
        SPHERE_BULLET = 50,
        LASER_BULLET = 51
    };

    void SetXVal(const int& xVal_) { xVal = xVal_; }
    void SetYVal (const int& yVal_) { yVal = yVal_; }
    int GetXVal() const { return xVal; }
    int GetYVal() const { return yVal; }

    void SetIsMove(const bool& isMove_) { isMove = isMove_; }
    bool GetIsMove() const { return isMove; }

    void SetBulletDir(const unsigned int& bulletDir_) { bulletDir = bulletDir_; }
    unsigned int GetBulletDir() const { return bulletDir; }

    void SetBulletType(const unsigned int& bulletType_) { bulletType = bulletType_; }
    unsigned int GetBulletType() const { return bulletType; }

    void HandleMove(const int& xBorder, const int& yBorder);
    bool LoadImgBullet(SDL_Renderer* des);
private:
    int xVal;
    int yVal;
    bool isMove;
    unsigned int bulletDir;
    unsigned int bulletType;
};

#endif