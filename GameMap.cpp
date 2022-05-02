#include"GameMap.h"

void GameMap::LoadMap(char* path) {
    FILE* fp = NULL;
    fopen_s(&fp, path, "rb");
    if (fp == NULL) {
        return;
    }

    gameMap.maxX = 0;
    gameMap.maxY = 0;

    for (int i = 0; i < MAX_MAP_Y; i++) {
        for (int j = 0; j < MAX_MAP_X; j++) {
            fscanf(fp, "%d", &gameMap.tile[i][j]);
            int val = gameMap.tile[i][j];
            if (val > 0) 
            {
                if (j > gameMap.maxX)
                    gameMap.maxX = j;
                if (i > gameMap.maxY)
                    gameMap.maxY = i;
            }
        }
    }

    gameMap.maxX = (gameMap.maxX + 1)*TILE_SIZE;
    gameMap.maxY = (gameMap.maxY + 1)*TILE_SIZE;

    gameMap.startX = 0;
    gameMap.startY = 0;

    gameMap.fileName = path;
    fclose(fp);
}

void GameMap::LoadTiles(SDL_Renderer* screen) {
    char fileImage[30];
    FILE* fp = NULL;

    for (int i = 0; i < 10; i++) {
        sprintf_s(fileImage, "map/%d.png", i);

        fopen_s(&fp, fileImage, "rb");
        if (fp == NULL) {
            continue;
        }

        fclose(fp);
        tileMat[i].LoadImg(fileImage, screen);
    }
}

void GameMap::DrawMap(SDL_Renderer* screen) {
    // coordinate we begin to render tile
    int x1 = 0;
    int y1 = 0;

    // coordinate we end up rendering
    int y2 = 0;
    int x2 = 0;

    int mapX = 0;
    int mapY = 0;

    mapX = gameMap.startX / TILE_SIZE;
    x1 = (gameMap.startX % TILE_SIZE)*-1;
    x2 = x1 + WINDOW_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    mapY = gameMap.startY / TILE_SIZE;
    y1 = (gameMap.startY % TILE_SIZE)*-1;
    y2 = y1 + WINDOW_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

    for (int i = y1; i < y2; i += TILE_SIZE) {
        mapX = gameMap.startX / TILE_SIZE;
        for (int j = x1; j < x2; j += TILE_SIZE) {
            int val = gameMap.tile[mapY][mapX];
            if (val > 0)
            {
                tileMat[val].SetRect(j, i);
                tileMat[val].Render(screen);
            }
            mapX++;
        }
        mapY++;
    }
}