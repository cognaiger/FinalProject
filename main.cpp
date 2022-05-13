#include"base.h" 
#include"BaseObject.h"
#include"GameMap.h"
#include"MainPlayer.h"
#include"Timer.h"
#include"ThreatObject.h"
#include"ExplosionObject.h"
#include"TextObject.h"

BaseObject gBackground;
TTF_Font* fontTime;


// set up window and renderer
bool init();

// load background on renderer
bool loadBackground(); 

// shut up everything
void close();

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

            if (TTF_Init() == -1) {
                success = false;
            } else {
                fontTime = TTF_OpenFont("font/dlxfont_.ttf", 15);
                if (fontTime == NULL) {
                    success = false;
                }
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

/*
create 20 static threats and 20 dynamic threats and set up
return 'listThreat' 
*/
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
            pThreat -> SetXPos(500 + i*700);
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

            BulletObject* pBullet = new BulletObject();
            pThreat -> InitBullet(pBullet, gSurface);

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
    
    ExplosionObject expThreat;
    bool tRet = expThreat.LoadImg("img/exp3.png", gSurface);
    if (tRet == false) {
        return -1;
    }
    expThreat.SetClip();

    ExplosionObject expMain;
    bool pRet = expMain.LoadImg("img/exp3.png", gSurface);
    if (pRet == false) 
        return -1;
    expMain.SetClip();


    // handle health of main player (> 3 -> die)
    int numDie = 0;


    // time text
    TextObject timeGame;
    timeGame.SetColor(TextObject::WHITE_TEXT);


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
                pThreat -> DoThreat(mapData);
                pThreat -> MakeBullet(gSurface, WINDOW_WIDTH, WINDOW_HEIGHT);
                pThreat -> Show(gSurface);

                SDL_Rect rectPlayer = gPlayer.GetRectFrame();
                bool bCol1 = false;
                std::vector<BulletObject*> tBulletList = pThreat -> GetBulletList();
                for (int jj = 0; jj < tBulletList.size(); jj++) {
                    BulletObject* ptBullet = tBulletList[jj];
                    if (ptBullet != NULL) {
                        bCol1 = SDLBase::CheckCollision(ptBullet -> GetRect(), rectPlayer) && 
                                ptBullet -> GetIsMove();
                        if (bCol1) {
                            pThreat -> RemoveBullet(jj);
                            break;
                        }
                    }
                }

                SDL_Rect RectThreat = pThreat -> GetRectFrame();
                bool bCol2 = SDLBase::CheckCollision(rectPlayer, RectThreat);

        

                if (bCol1 || bCol2) {
                    int widthExpFrame = expMain.GetFrameWidth();
                    int heightExpFrame = expMain.GetFrameHeight();
                    for (int i = 0; i < NUM_FRAME_EX; i++) {
                        int xPos = (gPlayer.GetRectFrame().x + gPlayer.GetRectFrame().w * 0.5)
                                  - widthExpFrame*0.5;
                        int yPos = (gPlayer.GetRectFrame().y + gPlayer.GetRectFrame().h * 0.5)
                                    - heightExpFrame*0.5;
                        
                        expMain.SetFrame(i);
                        expMain.SetRect(xPos, yPos);
                        expMain.Show(gSurface);
                        SDL_RenderPresent(gSurface);
                    }
                    
                    numDie++;
                    if (numDie <= 3) {
                        gPlayer.SetRect(0, 0);
                        gPlayer.SetComebackTime(60);
                        SDL_Delay(1000);
                        continue;
                    } else {
                        if (MessageBox(NULL, _T("Game Over"), _T("Info"), MB_OK | MB_ICONSTOP) == IDOK) {
                            pThreat -> free();
                            close();
                            SDL_Quit();
                            return 0;
                        }  
                    }
                }
            
            }
        }


        int frameExpWidth = expThreat.GetFrameWidth();
        int frameExpHeight = expThreat.GetFrameHeight();

        std::vector<BulletObject*> bulletArr = gPlayer.GetBulletList();
        for (int r = 0; r < bulletArr.size(); r++) {
            BulletObject* pBullet = bulletArr[r];
            if (pBullet != NULL) {
                for (int t = 0; t < threatList.size(); t++) {
                    ThreatObject* obThreat = threatList[t];
                    if (obThreat != NULL) {
                        SDL_Rect tRect;
                        tRect.x = obThreat -> GetRect().x;
                        tRect.y = obThreat -> GetRect().y;
                        tRect.w = obThreat -> GetWidthFrame();
                        tRect.h = obThreat -> GetHeightFrame();

                        SDL_Rect bRect = pBullet -> GetRect();

                        bool bCol = SDLBase::CheckCollision(bRect, tRect);

                        if (bCol) {
                            for (int ex = 0; ex < NUM_FRAME_EX; ex++) {
                                int xPos = pBullet -> GetRect().x - 0.5*frameExpWidth;
                                int yPos = pBullet -> GetRect().y - 0.5*frameExpHeight;

                                expThreat.SetFrame(ex);
                                expThreat.SetRect(xPos, yPos);
                                expThreat.Show(gSurface);
                            }

                            gPlayer.RemoveBullet(r);
                            obThreat -> free();
                            threatList.erase(threatList.begin() + t);
                        }
                    }
                }
            }
        }

        // Show game time
        std::string strTime = "Time: ";
        Uint32 timeVal = SDL_GetTicks() / 1000;
        Uint32 valTime = 300 - timeVal;
        if (valTime < 0) {
            if (MessageBox(NULL, _T("Game Over"), _T("Info"), MB_OK | MB_ICONSTOP) == IDOK) {
                quit = true;
                break;
            }
        } else {
            std::string strVal = std::to_string(valTime);
            strTime += strVal;

            timeGame.SetText(strTime);
            timeGame.LoadFromRenderText(fontTime, gSurface);
            timeGame.RenderText(gSurface, WINDOW_WIDTH - 200, 15);
        }

        SDL_RenderPresent(gSurface);

        int realImpTime = fpsTimer.GetTicks();
        int timeOneFrame = 1000/FPS;   // ms

        if (realImpTime < timeOneFrame) {
            int delayTime = timeOneFrame - realImpTime;
            SDL_Delay(delayTime);
        }
    }         // end game loop


    // free threat
    for (int i = 0; i < threatList.size(); i++) {
        ThreatObject* pThreat = threatList[i];
        if (pThreat != NULL) {
            pThreat -> free();
            pThreat = NULL;
        }
    }
    threatList.clear();

    // end program
    close();
    return 0;
}