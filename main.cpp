#include"base.h" 
#include"BaseObject.h"
#include"GameMap.h"
#include"MainPlayer.h"
#include"Timer.h"
#include"ThreatObject.h"

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

std::vector<ThreatObject*> MakeThreatList() {
    std::vector<ThreatObject*> listThreat;

    ThreatObject* dynamicThreat = new ThreatObject[20];
    for (int i = 0; i < 20; i++) {
        ThreatObject* pThreat = (dynamicThreat + i);
        if (pThreat != NULL) {
            pThreat -> LoadImg("img/threat_left.png", gSurface);
            pThreat -> SetClips();
            pThreat -> SetTypeMove(ThreatObject::MOVE_IN_SPACE_THREAT);
            pThreat -> SetInputLeft(1);
            pThreat -> SetXPos(500 + i*500);
            pThreat -> SetYPos(250);

            int pos1 = pThreat -> GetXPos() - 60;
            int pos2 = pThreat -> GetXPos() + 60;
            pThreat -> SetAnimationPos(pos1, pos2);

            listThreat.push_back(pThreat);
        }
    }


    ThreatObject* threatObj = new ThreatObject[20];
    for (int i = 0; i < 20; i++) {
        ThreatObject* pThreat = (threatObj + i);
        if (pThreat != NULL) {
            pThreat -> LoadImg("img/threat_level.png", gSurface);
            pThreat -> SetClips();
            pThreat -> SetTypeMove(ThreatObject::STATIC_THREAT);
            pThreat -> SetXPos(700 + i*1200);
            pThreat -> SetYPos(250);

            listThreat.push_back(pThreat);
        }
    }

    return listThreat;
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

    std::vector<ThreatObject*> threatList = MakeThreatList();
    
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

        gPlayer.HandleBullet(gSurface);
        gPlayer.SetMapXY(mapData.startX, mapData.startY);
        gPlayer.DoPlayer(mapData);
        gPlayer.Show(gSurface);

        mainMap.SetMap(mapData);
        mainMap.DrawMap(gSurface);

        for (int i = 0; i < threatList.size(); i++) {
            ThreatObject* pThreat = threatList[i];
            if (pThreat != NULL) {
                pThreat -> SetMapXY(mapData.startX, mapData.startY);
                pThreat -> ImpMoveType(gSurface);
                pThreat->DoThreat(mapData);
                pThreat->Show(gSurface);
            }
        }

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