#include"ThreatObject.h"

ThreatObject::ThreatObject() {
    widthFrame = 0;
    heightFrame = 0;
    xVal = 0.0;
    yVal = 0.0;
    xPos = 0.0;
    yPos = 0.0;
    onGround = 0;
    comeBackTime = 0;
    frame = 0;

    animationA = 0;
    animationB = 0;
    inputType.left = 0;
    typeMove = STATIC_THREAT;
}

ThreatObject::~ThreatObject() {

}

bool ThreatObject::LoadImg(std::string path, SDL_Renderer* screen) {
    bool ret = BaseObject::LoadImg(path, screen);
    if (ret) {
        widthFrame = rect.w/THREAT_FRAME_NUM;
        heightFrame = rect.h;
    }
    return ret;
}

void ThreatObject::SetClips() {
    if (widthFrame && heightFrame) {
        for (int i = 0; i < THREAT_FRAME_NUM; i++) {
            frameClip[i].x = i*widthFrame;
            frameClip[i].y = 0;
            frameClip[i].w = widthFrame;
            frameClip[i].h = heightFrame;
        }
    }
}

void ThreatObject::Show(SDL_Renderer* des) {
    if (comeBackTime == 0) {
        rect.x = xPos - mapX;
        rect.y = yPos - mapY;
        frame++;
        if (frame >= 8) {
            frame = 0;
        }

        SDL_Rect* currentClip = &frameClip[frame];
        SDL_Rect renderQuad = {rect.x, rect.y, widthFrame, heightFrame};
        SDL_RenderCopy(des, pObject, currentClip, &renderQuad);
    }
}

void ThreatObject::DoThreat(Map& mapData) {
    if (comeBackTime == 0) {
        xVal = 0;
        yVal += SDL_STANDARD_GRAVITY;
        if (yVal > THREAT_MAX_FALL_SPEED) {
            yVal = THREAT_MAX_FALL_SPEED;
        }

        if (inputType.left == 1) {
            xVal -= THREAT_SPEED;
        } else if (inputType.right == 1) {
            xVal += THREAT_SPEED;
        }

        CheckToMap(mapData);
    } else if (comeBackTime > 0) {
        comeBackTime--;
        if (comeBackTime == 0) {
            InitThreat();
        }
    }
}

void ThreatObject::CheckToMap(Map& mapData) {
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    // check horizontal
    int heightMin = heightFrame < TILE_SIZE ? heightFrame : TILE_SIZE;

    x1 = (xPos + xVal)/TILE_SIZE;
    x2 = (xPos + xVal + widthFrame)/TILE_SIZE;

    y1 = (yPos)/TILE_SIZE;
    y2 = (yPos + heightMin - 1)/TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)       // valid pos in map limit
    {
        if (xVal > 0)     // main player is moving right
        {
            int val1 = mapData.tile[y1][x2];
            int val2 = mapData.tile[y2][x2];

            if ((val1 != BLANK_TILE && val1 != COIN_TILE) || (val2 != BLANK_TILE && val2 != COIN_TILE)) {
                xPos = x2 * TILE_SIZE;
                xPos -= (widthFrame + 1);
                xVal = 0;
            } 
        } else if (xVal < 0)      // moving left
        {
            int val1 = mapData.tile[y1][x1];
            int val2 = mapData.tile[y2][x1];

        if ((val1 != BLANK_TILE && val1 != COIN_TILE) || (val2 != BLANK_TILE && val2 != COIN_TILE))
            {
                xPos = (x1 + 1) * TILE_SIZE;
                xVal = 0;
            }
        }
    }

    // check vertical
    int widthMin = widthFrame < TILE_SIZE ? widthFrame : TILE_SIZE;
    
    x1 = xPos/TILE_SIZE;
    x2 = (xPos + widthMin)/TILE_SIZE;

    y1 = (yPos + yVal)/TILE_SIZE;
    y2 = (yPos + yVal + heightFrame - 1)/TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) 
    {
        if (yVal > 0) {
            int val1 = mapData.tile[y2][x1];
            int val2 = mapData.tile[y2][x2];

            if ((val1 != BLANK_TILE && val1 != COIN_TILE) || (val2 != BLANK_TILE && val2 != COIN_TILE))
            {
                yPos = y2*TILE_SIZE;
                yPos -= (heightFrame + 1);
                yVal = 0;

                onGround = true;
            }
        } else if (yVal < 0) {
            int val1 = mapData.tile[y2][x1];
            int val2 = mapData.tile[y2][x2];

            if ((val1 != BLANK_TILE && val1 != COIN_TILE) || (val2 != BLANK_TILE && val2 != COIN_TILE))
            {
                yPos = (y1 + 1)*TILE_SIZE;
                yVal = 0;
            }
        }
    }

    xPos += xVal;
    yPos += yVal;

    if (xPos < 0) {           // can get over map limit
        xPos = 0;
    } else if(xPos + widthFrame > mapData.maxX) 
    {
        xPos = mapData.maxX - widthFrame - 1;
    }

    if (yPos > mapData.maxY) {    // fall into hole
        comeBackTime = 60;
    }
}

void ThreatObject::ImpMoveType(SDL_Renderer* screen) {
    if (typeMove == STATIC_THREAT) {
        ; // do nothing
    } else if (typeMove == MOVE_IN_SPACE_THREAT) {
        if (onGround == true) {
            if (xPos > animationB) {
                inputType.left = 1;
                inputType.right = 0;
                LoadImg("img/threat_left.png", screen);
            } else if (xPos < animationA) {
                inputType.left = 0;
                inputType.right = 1;
                LoadImg("img/threat_right.png", screen);
            }
        } else {
            if (inputType.left == 1) {
                LoadImg("img/threat_left.png", screen);
            } else {
                LoadImg("img/threat_right.png", screen);
            }
        }
    }
}

void ThreatObject::InitThreat() {
    xVal = 0;
    yVal = 0;
    if (xPos > 256) {
        xPos -= 256;
        animationA -= 256;
        animationB -= 256;
    } else {
        xPos = 0;
    }
    yPos = 0;
    inputType.left = 1;
}

void ThreatObject::InitBullet(BulletObject *pBullet, SDL_Renderer *screen) {
    if (pBullet != NULL) {
        pBullet -> SetBulletType(BulletObject::LASER_BULLET);
        bool ret = pBullet -> LoadImgBullet(screen);
        
        if (ret) {
            pBullet -> SetIsMove(true);
            pBullet -> SetBulletDir(BulletObject::DIR_LEFT);
            pBullet -> SetRect(rect.x + 5, rect.y + 10);
            pBullet -> SetXVal(15);
            bulletList.push_back(pBullet);
        }
        
    } 
}

void ThreatObject::MakeBullet(SDL_Renderer* screen, const int& xLimit, const int& yLimit) {
    for (int i = 0; i < bulletList.size(); i++) {
        BulletObject* pBullet = bulletList[i];
        if (pBullet != NULL) {
            if (pBullet -> GetIsMove()) {
                int bulletDistance = widthFrame + rect.x - pBullet -> GetRect().x;
                if (bulletDistance < 300) {
                    pBullet -> HandleMove(xLimit, yLimit);
                    pBullet -> Render(screen);
                } else {
                    pBullet -> SetIsMove(false);
                }
                
            } else {
                pBullet -> SetIsMove(true);
                pBullet -> SetRect(rect.x + 5, rect.y + 10);
            }
        }
    }
}

void ThreatObject::RemoveBullet(const int& idx) {
    int size = bulletList.size();
    if (size > 0 && idx < size) {
        BulletObject* pBullet = bulletList[idx];
        bulletList.erase(bulletList.begin() + idx);

        if (pBullet) {
            delete pBullet;
            pBullet = NULL;
        }
    }
}

SDL_Rect ThreatObject::GetRectFrame() {
    SDL_Rect rect_;
    rect_.x = rect.x;
    rect_.y = rect.y;
    rect_.w = widthFrame;
    rect_.h = heightFrame; 
    return rect_;
}