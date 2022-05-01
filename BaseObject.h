#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include"base.h"

// base class that handle render image
class BaseObject {
public:
    BaseObject();
    ~BaseObject();
    void SetRect(const int& x, const int& y) {rect.x = x, rect.y = y;};
    SDL_Rect GetRect() const { return rect; };
    SDL_Texture* GetObject() const { return pObject; };

    virtual bool LoadImg(std::string path, SDL_Renderer* screen);
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    void free();

protected:
    SDL_Texture* pObject = NULL;
    SDL_Rect rect;
};

#endif