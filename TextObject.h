#ifndef TEXT_OBEJECT_H
#define TEXT_OBJECT_H

#include"base.h"
#include"BaseObject.h"



class TextObject
{
public:
    TextObject();
    ~TextObject();

    enum TextColor
    {
        RED_TEXT = 0,
        WHITE_TEXT = 1,
        BLACK_TEXT = 2
    };

    bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen);
    void Free();

    void SetColor(Uint8 red, Uint8 green, Uint8 blue);
    void SetColor(int type);

    void RenderText(SDL_Renderer* screen, SDL_Rect* clip = NULL, 
                    double angle = 0.0, SDL_Point* center = NULL, 
                    SDL_RendererFlip flip = SDL_FLIP_NONE);

    int GetWidth() const { return rect.w; }
    int GetHeight() const { return rect.h; }

    void SetText(const std::string text) { strVal = text; }
    std::string GetText() const { return strVal; }
    void SetRect(const int& xp, const int& yp) { rect.x = xp, rect.y = yp; }
    SDL_Rect GetRect() const { return rect; }

private:
    std::string strVal;
    SDL_Color textColor;
    SDL_Texture* texture;
    SDL_Rect rect;
};


namespace Menu {
    // handle menu
    int ShowMenu(SDL_Renderer* des, TTF_Font* font);
}


#endif