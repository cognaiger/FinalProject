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

    // load texture into pObject and get information of its width and height
    virtual bool LoadImg(std::string path, SDL_Renderer* screen);

    // render texture to 'des' 
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);

    // destroy all things
    void free();

protected:
    // contain texture
    SDL_Texture* pObject = NULL;
    // contain info about rectangle the image will be displayed on renderer
    SDL_Rect rect;
};

#endif