#include "BaseObject.h"

BaseObject::BaseObject() {
    pObject = NULL;
    rect.x = 0;
    rect.y = 0;
    rect.h = 0;
    rect.w = 0;
}

BaseObject::~BaseObject() {
    free();
}

bool BaseObject::LoadImg(std::string path, SDL_Renderer* screen) {
    free();

    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadSurface = IMG_Load(path.c_str());
    if (loadSurface != NULL) {
        SDL_SetColorKey(loadSurface, SDL_TRUE, 
               SDL_MapRGB(loadSurface -> format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        newTexture = SDL_CreateTextureFromSurface(screen, loadSurface);
        if (newTexture != NULL) {
            rect.w = loadSurface -> w;
            rect.h = loadSurface -> h;
        }

        SDL_FreeSurface(loadSurface);
    }

    pObject = newTexture;
    return pObject != NULL;
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip /* = NULL */) {
    SDL_Rect renderquad = {rect.x, rect.y, rect.w, rect.h};
    SDL_RenderCopy(des, pObject, clip, &renderquad);
}

void BaseObject::free() {
    if (pObject != NULL) {
        SDL_DestroyTexture(pObject);
        pObject = NULL;
        rect.h = 0;
        rect.w = 0;
    }
}



