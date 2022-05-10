#include "ExplosionObject.h"

ExplosionObject::ExplosionObject() {
    frameWidth = 0;
    frameHeight = 0;
    frame = 0;
}

ExplosionObject::~ExplosionObject() {

}

bool ExplosionObject::LoadImg(std::string path, SDL_Renderer* screen) {
    bool ret = BaseObject::LoadImg(path, screen);

    if (ret) {
        frameWidth = rect.w/NUM_FRAME_EX;
        frameHeight = rect.h;
    }

    return ret;
}

void ExplosionObject::SetClip() {
    if (frameHeight && frameWidth) {
        for (int i = 0; i < NUM_FRAME_EX; i++) {
            frameClip[i].x = i*frameWidth;
            frameClip[i].y = 0;
            frameClip[i].w = frameWidth;
            frameClip[i].h = frameHeight;
        }
    }
}

void ExplosionObject::Show(SDL_Renderer* screen) {
    SDL_Rect* currentClip = &frameClip[frame];
    SDL_Rect renderQuad = {rect.x, rect.y, frameWidth, frameHeight};
    if (currentClip != NULL) {
        renderQuad.w = currentClip -> w;
        renderQuad.h = currentClip -> h;
    }

    SDL_RenderCopy(screen, pObject, currentClip, &renderQuad);
}