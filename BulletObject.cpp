#include"BulletObject.h"

BulletObject::BulletObject() {
    xVal = 0;
    yVal = 0;
    isMove = false;
}

BulletObject::~BulletObject() {

}

void BulletObject::HandleMove(const int& xBorder, const int& yBorder) {
    if (bulletDir == DIR_RIGHT) {
        rect.x += xVal;
        if (rect.x > xBorder) {
        isMove = false;
        }
    } else if (bulletDir == DIR_LEFT) {
        rect.x -= xVal;
        if (rect.x < 0) {
            isMove = false;
        }
    }
    
}