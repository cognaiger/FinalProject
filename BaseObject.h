#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include"base.h"

// base class that handle object needed rendering on screen
class BaseObject {
public:
    BaseObject();
    ~BaseObject();

    // set top-left coordinate of rectangle to render image on screen
    void SetRect(const int& x, const int& y) {rect.x = x, rect.y = y;};
    
    SDL_Rect GetRect() const { return rect; };
    SDL_Texture* GetObject() const { return pObject; };

    // load texture into pObject and get information of its width and height
    virtual bool LoadImg(std::string path, SDL_Renderer* screen);

    // render texture to 'des' base on width and height of source texture (rect.x = rect.y = 0)
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);

    // destroy all things
    void free();

protected:
    // contain texture of object
    SDL_Texture* pObject = NULL;

    // contain info about rectangle of the image will be displayed on renderer
    SDL_Rect rect;
};

#endif