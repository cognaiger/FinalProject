#include"base.h" 
#include"BaseObject.h"
#include"GameMap.h"
#include"MainPlayer.h"
#include"Timer.h"

// set up window and renderer
bool init();

// load background on renderer
bool loadBackground(); 

// shut up everything
void close();

BaseObject gBackground;

// set up window and renderer
bool init()
{
    bool success = true;
    if( SDL_Init( SDL_INIT_VIDEO ) >= 0 )
    {
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow != NULL )
        {
            gSurface = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gSurface == NULL) 
            {
                std::cout << "Can't create renderer! SDL error: " << SDL_GetError() << std::endl;
                success = 0;
            } else 
            {
                SDL_SetRenderDrawColor(gSurface, RENDER_DRAW_COLOR,
                            RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
                int imgFlags = IMG_INIT_PNG;
                if ( !(IMG_Init(imgFlags) && imgFlags) ) 
                    success = false;
            }
        } else 
        {
            std::cout << "Can't create window! SDL error: " << SDL_GetError() << std::endl;
            success = false;
        }
    } else {
        std::cout << "Can't initialize SDL video! SDL error: " << SDL_GetError() << std::endl;
        success = 0;
    }

    return success;
}
 
void close()
{
    gBackground.free();

    SDL_DestroyRenderer(gSurface);
    gSurface = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();
}
 

bool loadBackground() {
    bool ret = gBackground.LoadImg("img/background.png", gSurface);
    if (ret == false) 
        return false;
    return true;
}
 
 
int main(int argc, char* argv[])
{
    if (init() == false)
        return -1;

    if (loadBackground() == 0)
        return -1;

    Timer fpsTimer;

    GameMap mainMap;
    char pathMap[] = "map/map01.dat";
    mainMap.LoadMap(pathMap);
    mainMap.LoadTiles(gSurface);
    Map mapData = mainMap.GetMap();

    MainPlayer gPlayer;
    gPlayer.LoadImg("img/player_right.png", gSurface);
    gPlayer.SetClips();
    
    bool quit = false;

    // game loop
    while (!quit) {
        fpsTimer.start();

        while (SDL_PollEvent(&gEvent) != 0) {
            if (gEvent.type == SDL_QUIT) {
                quit = true;
            }

            gPlayer.HandleInput(gEvent, gSurface);
        }

        SDL_SetRenderDrawColor(gSurface, RENDER_DRAW_COLOR,
                            RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(gSurface);

        gBackground.Render(gSurface);

        gPlayer.SetMapXY(mapData.startX, mapData.startY);
        gPlayer.DoPlayer(mapData);
        gPlayer.Show(gSurface);

        mainMap.SetMap(mapData);
        mainMap.DrawMap(gSurface);

        SDL_RenderPresent(gSurface);

        int realImpTime = fpsTimer.GetTicks();
        int timeOneFrame = 1000/FPS;   // ms

        if (realImpTime < timeOneFrame) {
            int delayTime = timeOneFrame - realImpTime;
            SDL_Delay(delayTime);
        }
    }
 
    close();
    return 0;
}