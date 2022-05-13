
#include "BossObject.h"


BossObject::BossObject()
{
    frame = 0;
    xVal = 0.0;
    yVal = 0.0;
    xPos = 0;
    yPos = 0;
    widthFrame = 0;
    heightFrame = 0;
    thinkTime = 0;
    mapX = 0;
    mapY = 0;
}

BossObject::~BossObject()
{

}

bool BossObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);

    if (ret == true)
    {
        widthFrame = rect.w/FRAME_NUM_32;
        heightFrame = rect.h;
    }

    return ret;
}

void BossObject::SetClips()
{
    //Clip the sprites
    if (widthFrame > 0 && heightFrame > 0)
    {
        for (int i = 0; i < FRAME_NUM_32; ++i)
        {
            frameClip[i].x = widthFrame*i;
            frameClip[i].y = 0;
            frameClip[i].w = widthFrame;
            frameClip[i].h = heightFrame;
        }
    }
}


void BossObject::Show(SDL_Renderer* des)
{
    if (thinkTime == 0)
    {
        rect.x = xPos - mapX;
        rect.y = yPos- mapY;
        frame++;
        if( frame >= 32 )
        {
            frame = 0;
        }

        SDL_Rect* currentClip = &frameClip[frame];
        SDL_Rect renderQuad = {rect.x, rect.y, widthFrame, heightFrame};
        if (currentClip != NULL)
        {
            renderQuad.w = currentClip->w;
            renderQuad.h = currentClip->h;
        }

        SDL_RenderCopy(des, pObject, currentClip, &renderQuad);
    }
}

void BossObject::DoPlayer(Map& g_map)
{
    if (thinkTime == 0)
    {
        xVal = 0;
        yVal += GRAVITY_SPEED;

        if (yVal >= MAX_FALL_SPEED)
        {
            yVal = MAX_FALL_SPEED;
        }

        if (inputType.left == 1)
        {
            xVal -= BOSS_SPEED;
        }

        else if (inputType.right == 1)
        {
            xVal+= BOSS_SPEED;
        }

        if (inputType.jump == 1)
        {
            if (onGround == 1)
            {
                yVal = -PLAYER_HIGHT_VAL;
            }

            inputType.jump = 0;
        }

        CheckToMap(g_map);

        //CenterEntityOnMap(g_map);
    }

    if (thinkTime > 0)
    {
        thinkTime--;

        if (thinkTime == 0)
        {
            InitPlayer();
        }
    }
}

void BossObject::InitPlayer()
{
    xVal = 0;
    yVal = 0;

    if (xPos > 256)
    {
        xPos -= 256;
    }
    else
        xPos = 0;
    yPos = 0;
    thinkTime = 0;
    inputType.left = 1;
}

/*
void BossObject::CenterEntityOnMap(Map& g_map)
{
    g_map.startX = xPos - (WINDOW_WIDTH/2);

    if (g_map.startX < 0)
    {
        g_map.startX = 0;
    }

    else if (g_map.startX + SCREEN_WIDTH >= g_map.max_x_)
    {
        g_map.start_x_= g_map.max_x_ - SCREEN_WIDTH;
    }

    g_map.start_y_ = y_pos_ - (SCREEN_HEIGHT / 2);

    if (g_map.start_y_ < 0)
    {
        g_map.start_y_ = 0;
    }

    else if (g_map.start_y_+ SCREEN_HEIGHT >= g_map.max_y_)
    {
        g_map.start_y_ = g_map.max_y_ - SCREEN_HEIGHT;
    }
}
*/

void BossObject::CheckToMap(Map& g_map)
{
    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;

    onGround = 0;

    //Check Horizontal
    int heightMin = heightFrame; //SDLCommonFunc::GetMin(height_frame_, TILE_SIZE);

    /*
    x1,y1***x2
    *       *
    *       *
    *       *
    *y2******

    */
    x1 = (xPos + xVal) / TILE_SIZE;
    x2 = (xPos + xVal + widthFrame - 1) / TILE_SIZE;

    y1 = (yPos) / TILE_SIZE;
    y2 = (yPos + heightMin - 1) / TILE_SIZE;

    // Check x1, x2 with full width of map
    // Check y1, y2 with full heigth of map
    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (xVal > 0) // when object is moving by right  ===>
        {
            // Check current position of map. It is not blank_tile.
            if ((g_map.tile[y1][x2] != BLANK_TILE) || (g_map.tile[y2][x2] != BLANK_TILE))
            {
                // Fixed post of object at current post of map.
                // => Cannot moving when press button
                xPos = x2 * TILE_SIZE;
                xPos -= widthFrame + 1;
                xVal = 0; // cannot moving
            }
        }
        else if (xVal < 0) // When moving by left    <====
        {
            if ((g_map.tile[y1][x1] != BLANK_TILE) || (g_map.tile[y2][x1] != BLANK_TILE))
            {
                xPos = (x1 + 1) * TILE_SIZE;
                xVal = 0;
            }
        }
    }


    // Check vertical
    int widthMin = widthFrame;// SDLCommonFunc::GetMin(width_frame_, TILE_SIZE);

    x1 = (xPos) / TILE_SIZE;
    x2 = (xPos + widthMin) / TILE_SIZE;

    y1 = (xPos + yVal) / TILE_SIZE;
    y2 = (yPos + yVal + heightFrame) / TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (yVal > 0)
        {
            //Similar for vertical
            if ((g_map.tile[y2][x1] != BLANK_TILE) || (g_map.tile[y2][x2] != BLANK_TILE))
            {
                yPos = y2 * TILE_SIZE;
                yPos -= heightFrame;

                yVal = 0;

                onGround = 1;
            }
        }
        else if (yVal < 0)
        {
            if ((g_map.tile[y1][x1] != BLANK_TILE) || (g_map.tile[y1][x2] != BLANK_TILE))
            {
                yPos = (y1 + 1) * TILE_SIZE;

                yVal = 0;
            }
        }
    }

    //If there is not collision with map tile. 
    xPos += xVal;
    yPos += yVal;

    if (xPos < 0)
    {
        xPos = 0;
    }
    else if (xPos + widthFrame >= g_map.maxX)
    {
        xPos = g_map.maxX - widthFrame - 1;
    }

    if (yPos > g_map.maxY)
    {
        thinkTime = 60;
    }
}

void BossObject::InitBullet(SDL_Renderer* screen)
{
    BulletObject* p_bullet = new BulletObject();
    bool ret = p_bullet->LoadImg("img/boss bullet.png", screen);
    if (ret)
    {
        p_bullet->SetBulletDir(BulletObject::DIR_LEFT);
        p_bullet->SetIsMove(true);
        p_bullet->SetRect(rect.x - 50, rect.y + heightFrame - 30);
        p_bullet->SetXVal(15);
        bulletList.push_back(p_bullet);
    }
}


void BossObject::MakeBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit)
{
    if (frame == 18)
    {
        InitBullet(des);
    }

    for (int i = 0; i < bulletList.size(); i++)
    {
        BulletObject* p_bullet = bulletList.at(i);
        if (p_bullet != NULL)
        {
            if (p_bullet -> GetIsMove())
            {
                p_bullet -> HandleMove(x_limit, y_limit);
                p_bullet -> Render(des);
            }
            else
            {
               p_bullet -> free();
               bulletList.erase(bulletList.begin() + i);
            }
        }
    }
}