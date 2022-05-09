#include"BulletObject.h"

BulletObject::BulletObject() {
    xVal = 0;
    yVal = 0;
    isMove = false;
    bulletDir = DIR_RIGHT;
    bulletType = SPHERE_BULLET;
}

BulletObject::~BulletObject() {

}

bool BulletObject::LoadImgBullet(SDL_Renderer* des) {
    bool ret = false;
    if (bulletType == LASER_BULLET) {
        ret = LoadImg("img/laser_bullet.png", des);
    } else {
        ret = LoadImg("img/bullet.png", des);
    }
    return ret;
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
    } else if (bulletDir == DIR_UP) {
        rect.y -= yVal;
        if (rect.y < 0) {
            isMove = false;
        }
    } else if (bulletDir == DIR_UPLEFT) {
        rect.x -= xVal;
        if (rect.x < 0) {
            isMove = false;
        }

        rect.y -= yVal;
        if (rect.y < 0) {
            isMove = 0;
        }
    } else if (bulletDir == DIR_UPRIGHT) {
        rect.x += xVal;
        if (rect.x > xBorder) {
            isMove =false;
        }

        rect.y -= yVal;
        if (rect.y < 0) {
            isMove = false;
        }
    } else if (bulletDir == DIR_DOWN) {
        rect.y += yVal;
        if (rect.y > yBorder) {
            isMove = false;
        }
    } else if (bulletDir == DIR_DOWNLEFT) {
        rect.x -= xVal;
        if (rect.x < 0) {
            isMove = false;
        }

        rect.y += yVal;
        if (rect.y > yBorder) {
            isMove = false;
        }
    } else if (bulletDir == DIR_DOWNRIGHT) {
        rect.x += xVal;
        if (rect.x > xBorder) {
            isMove = false;
        }

        rect.y += yVal;
        if (rect.y > yBorder) {
            isMove = false;
        }
    }
    
}