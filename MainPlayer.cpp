#include"MainPlayer.h"

MainPlayer::MainPlayer() {
    frame = 0;
    xPos = 0;
    yPos = 0;
    xVal = 0;
    yVal = 0;
    widthFrame = 0;
    heightFrame = 0;
    status = WALK_NONE;
    inputType.right = 0;
    inputType.left = 0;
    inputType.down = 0;
    inputType.jump = 0;
    inputType.up = 0;
    onGround = false;
    mapX = 0;
    mapY = 0;
    comeBackTime = 0;
    coinCount = 0;
}

MainPlayer::~MainPlayer() {

}

bool MainPlayer::LoadImg(std::string path, SDL_Renderer* screen) {
    bool ret = BaseObject::LoadImg(path, screen);
    if (ret == true) {
        widthFrame = rect.w/8;
        heightFrame = rect.h;
    }
    return ret;
}

void MainPlayer::SetClips() {
    if (widthFrame && heightFrame) {
        for (int i = 0; i < FRAME_NUM; i++) {
            frameCLip[i].x = i*widthFrame;
            frameCLip[i].y = 0;
            frameCLip[i].w = widthFrame;
            frameCLip[i].h = heightFrame;
        }
    }
    
}

void MainPlayer::Show(SDL_Renderer* des) {
    UpdateImagePlayer(des);

    if (inputType.left == 1 || inputType.right == 1) 
    {
        frame++;
    } else {
        frame = 0;
    }

    if (frame >= 8) {
        frame = 0;
    }

    if (comeBackTime == 0) {
        // modify player position relatively to map
        rect.x = xPos - mapX;
        rect.y = yPos - mapY;

        SDL_Rect* currentClip = &frameCLip[frame];
        SDL_Rect renderQuad = {rect.x, rect.y, widthFrame, heightFrame};
        SDL_RenderCopy(des, pObject, currentClip, &renderQuad);
    }
}

void MainPlayer::HandleInput(SDL_Event events, SDL_Renderer* screen) {
    if (events.type == SDL_KEYDOWN) 
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_RIGHT:
            status = WALK_RIGHT;
            inputType.right = 1;
            inputType.left = 0;
            break;
        case SDLK_LEFT:
            status = WALK_LEFT;
            inputType.left = 1;
            inputType.right = 0;
            break;
        }
    } else if (events.type == SDL_KEYUP)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_RIGHT:
            inputType.right = 0;
            break;
        case SDLK_LEFT:
            inputType.left = 0;
            break;
        }
    }

    if (events.type == SDL_MOUSEBUTTONDOWN)         // jump may be used with run left or right
    {
        if (events.button.button == SDL_BUTTON_RIGHT) {
            inputType.jump = 1;
        } else if (events.button.button == SDL_BUTTON_LEFT) {
            BulletObject* pBullet = new BulletObject();
            pBullet -> SetBulletType(BulletObject::LASER_BULLET);
            pBullet -> LoadImgBullet(screen);

            if (status == WALK_LEFT) {
                pBullet -> SetBulletDir(BulletObject::DIR_LEFT);
                pBullet -> SetRect(rect.x, rect.y + heightFrame*0.25);
            } else {
                pBullet -> SetBulletDir(BulletObject::DIR_RIGHT);
                pBullet -> SetRect(rect.x + widthFrame - 20, rect.y + heightFrame*0.25);
            }

            pBullet -> SetXVal(20);
            pBullet -> SetYVal(20);
            pBullet -> SetIsMove(true);

            pBulletList.push_back(pBullet);
        }
    }
}

void MainPlayer::DoPlayer(Map& mapData) {
    if (comeBackTime == 0) {
        xVal = 0;
        yVal += GRAVITY_SPEED;

        if (yVal >= MAX_FALL_SPEED) {
            yVal = MAX_FALL_SPEED;
        }

        if (inputType.left == 1) {
            xVal -= PLAYER_SPEED;
        } else if (inputType.right == 1) {
            xVal += PLAYER_SPEED;
        }

        if (inputType.jump == 1) {
            if (onGround == true) {
                yVal = -PLAYER_JUMP_VALUE;
                onGround = false;
            }
            inputType.jump = 0;
        }

        CheckToMap(mapData);
        CenterEntityOnMap(mapData);
    }

    if (comeBackTime > 0) {
        comeBackTime--;
        if (comeBackTime == 0) {             // reset again
            onGround = false;
            if (xPos > 256) {
                xPos -= 256;        // 4 tile map
            } else {
                xPos = 0;
            }

            yPos = 0;
            xVal = 0;
            yVal = 0;
        }
    }
}

void MainPlayer::CenterEntityOnMap(Map& mapData) {
    mapData.startX = xPos - (WINDOW_WIDTH/2);
    if (mapData.startX < 0) {
        mapData.startX = 0;
    }
    if (mapData.startX + WINDOW_WIDTH >= mapData.maxX) {
        mapData.startX = mapData.maxX - WINDOW_WIDTH;
    }

    mapData.startY = yPos - (WINDOW_HEIGHT/2);
    if (mapData.startY < 0) {
        mapData.startY = 0;
    }
    if (mapData.startY + WINDOW_HEIGHT >= mapData.maxY) {
        mapData.startY = mapData.maxY - WINDOW_HEIGHT;
    }
}

void MainPlayer::CheckToMap(Map& mapData) {
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

            if (val1 == COIN_TILE || val2 == COIN_TILE) {
                mapData.tile[y1][x2] = 0;
                mapData.tile[y2][x2] = 0;
                IncreaseCoin();
            } else if (val1 != BLANK_TILE || val2 != BLANK_TILE) {
                xPos = x2 * TILE_SIZE;
                xPos -= (widthFrame + 1);
                xVal = 0;
            } 
        } else if (xVal < 0)      // moving left
        {
            int val1 = mapData.tile[y1][x1];
            int val2 = mapData.tile[y2][x1];

            if (val1 == COIN_TILE || val2 == COIN_TILE) {
                mapData.tile[y1][x1] = 0;
                mapData.tile[y2][x1] = 0;
                IncreaseCoin();
            } else if (val1 != BLANK_TILE || val2 != BLANK_TILE)
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
            if (val1 == COIN_TILE || val2 == COIN_TILE) {
                mapData.tile[y2][x1] = 0;
                mapData.tile[y2][x2] = 0;
                IncreaseCoin();
            } else if (val1 != BLANK_TILE || val2 != BLANK_TILE)
            {
                yPos = y2*TILE_SIZE;
                yPos -= (heightFrame + 1);
                yVal = 0;

                onGround = true;
                if (status == WALK_NONE) {
                    status = WALK_RIGHT;
                }
            }
        } else if (yVal < 0) {
            int val1 = mapData.tile[y2][x1];
            int val2 = mapData.tile[y2][x2];

            if (val1 == COIN_TILE || val2 == COIN_TILE) {
                mapData.tile[y2][x1] = 0;
                mapData.tile[y2][x2] = 0;
                IncreaseCoin();
            } else if (val1 != BLANK_TILE || val2 != BLANK_TILE)
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

void MainPlayer::UpdateImagePlayer(SDL_Renderer* des) {
    if (onGround == true) {
        if (status == WALK_LEFT) {
            LoadImg("img/player_left.png", des);
        } else {
            LoadImg("img/player_right.png", des);
        }
    } else {
        if (status == WALK_LEFT) {
            LoadImg("img/jum_left.png", des);
        } else {
            LoadImg("img/jum_right.png", des);
        }
    }
}

void MainPlayer::HandleBullet(SDL_Renderer* des) {
    for (int i = 0; i < pBulletList.size(); i++) {
        BulletObject* pBullet = pBulletList[i];
        if (pBullet != NULL) {
            if (pBullet -> GetIsMove() == true) {
                pBullet -> HandleMove(WINDOW_WIDTH, WINDOW_HEIGHT);
                pBullet -> Render(des);
            }
            else {
                pBulletList.erase(pBulletList.begin() + i);
                if (pBullet != NULL) {
                    delete pBullet;
                    pBullet = NULL;
                }
            }
        }
    }
}

void MainPlayer::IncreaseCoin() {
    coinCount++;
}

void MainPlayer::RemoveBullet(const int& idx) {
    int size = pBulletList.size();
    if (size > 0 && idx < size) {
        BulletObject* pBullet = pBulletList[idx];
        pBulletList.erase(pBulletList.begin() + idx);

        if (pBullet) {
            delete pBullet;
            pBullet = NULL;
        }
    }
}

SDL_Rect MainPlayer::GetRectFrame() {
    SDL_Rect rect_;
    rect_.x = rect.x;
    rect_.y = rect.y;
    rect_.w = widthFrame;
    rect_.h = heightFrame; 
    return rect_;
}