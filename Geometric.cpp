#include"Geometric.h"

void Geometric::RenderRectangle(const GeometricFormat& geoSize, 
                                const ColorData& colorData, SDL_Renderer* screen)
{
    SDL_Rect fillRect = {geoSize.left, geoSize.top, geoSize.width, geoSize.height};
    SDL_SetRenderDrawColor(screen, colorData.red, colorData.green, colorData.blue, 0xFF);
    SDL_RenderFillRect(screen, &fillRect);
}

void Geometric::RenderOutline(const GeometricFormat& geoSize, 
                                const ColorData& colorData, SDL_Renderer* screen)
{
    SDL_Rect outRect = {geoSize.left, geoSize.top, geoSize.width, geoSize.height};
    SDL_SetRenderDrawColor(screen, colorData.red, colorData.green, colorData.blue, 0xFF);
    SDL_RenderDrawRect(screen, &outRect);   
}