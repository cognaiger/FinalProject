#include"TextObject.h"

TextObject::TextObject() {
    textColor.r = 255;
    textColor.g = 255;
    textColor.b = 255;
    texture = NULL;
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;
}

TextObject::~TextObject() {

}

bool TextObject::LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, strVal.c_str(), textColor);
    if (textSurface) {
        texture = SDL_CreateTextureFromSurface(screen, textSurface);
        rect.w = textSurface -> w;
        rect.h = textSurface -> h;

        SDL_FreeSurface(textSurface);
    }

    return texture != NULL;
}

void TextObject::Free() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}

void TextObject::SetColor(Uint8 red, Uint8 green, Uint8 blue) {
    textColor.r = red;
    textColor.g = green;
    textColor.b = blue;
}

void TextObject::SetColor(int type) {
    if (type == RED_TEXT) {
        SDL_Color color = {255, 0, 0};
        textColor = color;
    } else if (type == WHITE_TEXT) {
        SDL_Color color = {255, 255, 255};
        textColor = color;
    } else if (type == BLACK_TEXT) {
        SDL_Color color = {0, 0, 0};
        textColor = color;
    }
}

void TextObject::RenderText(SDL_Renderer* screen,  
                            SDL_Rect* clip /* = NULL */, double angle /* = 0.0 */, 
                            SDL_Point* center /* = NULL */, 
                            SDL_RendererFlip flip /* = SDL_FLIP_NONE */)
{
    SDL_Rect renderQuad = {rect.x, rect.y, rect.w, rect.h};
    if (clip != NULL) {
        renderQuad.w = clip -> w;
        renderQuad.h = clip -> h;
    }

    SDL_RenderCopyEx(screen, texture, clip, &renderQuad, angle, center, flip);
}


BaseObject gMenu;


int Menu::ShowMenu(SDL_Renderer* des, TTF_Font* font) {
    if (gMenu.LoadImg("img/menugame.png", des) == 0) {
        return 1;
    }

    const int MenuItemNum = 2;
    SDL_Rect posArr[MenuItemNum];
    posArr[0].x = WINDOW_WIDTH*0.5 - 40;
    posArr[0].y = 400;

    posArr[1].x = WINDOW_WIDTH*0.5 - 25;
    posArr[1].y = 500;

    TextObject textMenu[MenuItemNum];
    textMenu[0].SetText("Play Game");
    textMenu[0].SetColor(TextObject::BLACK_TEXT);
    textMenu[0].SetRect(posArr[0].x, posArr[0].y);

    textMenu[1].SetText("Exit");
    textMenu[1].SetColor(TextObject::BLACK_TEXT);
    textMenu[1].SetRect(posArr[1].x, posArr[1].y);

    bool selected[MenuItemNum] = {0, 0};
    int xm = 0;
    int ym = 0;
    SDL_Event mEvent;
    while (true) {
        gMenu.Render(des);
        for (int i = 0; i < MenuItemNum; i++) {
            textMenu[i].LoadFromRenderText(font, des);
            textMenu[i].RenderText(des);
            // textMenu[i].CreateGameText(font, des);
        }

        while (SDL_PollEvent(&mEvent)) {
            switch (mEvent.type) 
            {
            case SDL_QUIT:
                return 1;
            case SDL_MOUSEMOTION:
                xm = mEvent.motion.x;
                ym = mEvent.motion.y;

                for (int i = 0; i < MenuItemNum; i++) {
                    if (SDLBase::CheckFocusWithRect(xm, ym, textMenu[i].GetRect()) == 1) {
                        if (selected[i] == false) {
                            selected[i] = true;
                            textMenu[i].SetColor(TextObject::RED_TEXT);
                        }
                    }
                    else {
                        if (selected[i] == true) {
                            selected[i] = false;
                            textMenu[i].SetColor(TextObject::BLACK_TEXT);
                        }
                    }
                }

                break;

            case SDL_MOUSEBUTTONDOWN:
                xm = mEvent.button.x;
                ym = mEvent.button.y;
                for (int i = 0; i < MenuItemNum; i++) {
                    if (SDLBase::CheckFocusWithRect(xm, ym, textMenu[i].GetRect()) == 1) {
                        return i;
                    }
                }
            
            case SDL_KEYDOWN:
                if (mEvent.key.keysym.sym == SDLK_ESCAPE) {
                    return 1;
                }

            default:
                break;
            }

        }
        SDL_RenderPresent(des);
    }

    return 1;
}
