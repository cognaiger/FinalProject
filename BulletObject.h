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
    };

    void SetXVal(const int& xVal_) { xVal = xVal_; }
    void SetYVal (const int& yVal_) { yVal = yVal_; }
    int GetXVal() const { return xVal; }
    int GetYVal() const { return yVal; }

    void SetIsMove(const bool& isMove_) { isMove = isMove_; }
    bool GetIsMove() const { return isMove; }

    void SetBulletDir(const unsigned int& bulletDir_) { bulletDir = bulletDir_; }
    unsigned int GetBulletDir() const { return bulletDir; }

    void HandleMove(const int& xBorder, const int& yBorder);
private:
    int xVal;
    int yVal;
    bool isMove;
    unsigned int bulletDir;
};

#endif