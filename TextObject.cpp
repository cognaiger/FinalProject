#include"TextObject.h"

TextObject::TextObject() {
    textColor.r = 255;
    textColor.g = 255;
    textColor.b = 255;
    texture = NULL;
}

TextObject::~TextObject() {

}

bool TextObject::LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, strVal.c_str(), textColor);
    if (textSurface) {
        texture = SDL_CreateTextureFromSurface(screen, textSurface);
        width = textSurface -> w;
        height = textSurface -> h;

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

void TextObject::RenderText(SDL_Renderer* screen, int xp, int yp, 
                            SDL_Rect* clip /* = NULL */, double angle /* = 0.0 */, 
                            SDL_Point* center /* = NULL */, 
                            SDL_RendererFlip flip /* = SDL_FLIP_NONE */)
{
    SDL_Rect renderQuad = {xp, yp, width, height};
    if (clip != NULL) {
        renderQuad.w = clip -> w;
        renderQuad.h = clip -> h;
    }

    SDL_RenderCopyEx(screen, texture, clip, &renderQuad, angle, center, flip);
}