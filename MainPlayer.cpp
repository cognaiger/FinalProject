#include"MainPlayer.h"

MainPlayer::MainPlayer() {
    frame = 0;
    xPos = 0;
    yPos = 0;
    xVal = 0;
    yVal = 0;
    widthFrame = 0;
    heightFrame = 0;
    status = -1;
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
    for (int i = 0; i < FRAME_NUM; i++) {
        frameCLip[i].x = i*widthFrame;
        frameCLip[i].y = 0;
        frameCLip[i].w = widthFrame;
        frameCLip[i].h = heightFrame;
    }
}

void MainPlayer::Show(SDL_Renderer* des) {
    if (status == WALK_LEFT) 
    {
        LoadImg("img/player_left.png", des);
    } else
    {
        LoadImg("img/player_right.png", des);
    }

    if (inputType.left == 1 || inputType.right == 1) 
    {
        frame++;
    } else {
        frame = 0;
    }

    if (frame >= 8) {
        frame = 0;
    }

    rect.x = xPos;
    rect.y = yPos;

    SDL_Rect* currentClip = &frameCLip[frame];
    SDL_Rect renderQuad = {rect.x, rect.y, widthFrame, heightFrame};
    SDL_RenderCopy(des, pObject, currentClip, &renderQuad);
}

void MainPlayer::HandleInput(SDL_Event events, SDL_Renderer* screen) {
    if (events.type == SDL_KEYDOWN) 
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_RIGHT:
            status = WALK_RIGHT;
            inputType.right = 1;
            break;
        case SDLK_LEFT:
            status = WALK_LEFT;
            inputType.left = 1;
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
}