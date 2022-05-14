

#ifndef BOSS_OBJECT_H_
#define BOSS_OBJECT_H_


#include "BaseObject.h"
#include "Base.h"
#include "BulletObject.h"
#include "GameMap.h"

#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10

#define BOSS_SPEED 2
#define PLAYER_HIGHT_VAL 18;

#define FRAME_NUM_32 32

class BossObject : public BaseObject
{
public:
    BossObject();
    ~BossObject();
    void SetXVal(int xp) { xVal = xp; }
    void SetYVal(int yp) { yVal = yp; }

    void SetXPos(const int& xps) { xPos = xps; }
    void SetYPos(const int& yps) { yPos = yps; }
    int GetXPos() { return xPos; }
    int GetYPos() { return yPos; }

    void Show(SDL_Renderer* des);
    bool LoadImg(std::string path, SDL_Renderer* screen);
    void SetClips();

    int GetWidthFrame() const { return widthFrame; }
    int GetHeightFrame() const { return heightFrame; }

    void SetMapXY(const int map_x, const int map_y) { mapX = map_x, mapY = map_y; };

    void CheckToMap(Map& g_map);
    void CenterEntityOnMap(Map& g_map);
    void DoPlayer(Map& g_map);
    void InitPlayer();
    std::vector<BulletObject*> GetBulletList() const {return bulletList;}
    void SetBulletList(const std::vector<BulletObject*>& am_list) {bulletList = am_list;}

    void InitBullet(SDL_Renderer* screen);
    void MakeBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit);

private:
    int mapX;
    int mapY;
    int onGround;
    int thinkTime;
    Input inputType;
    int frame;
    SDL_Rect frameClip[FRAME_NUM_32];
    int xPos;
    int yPos;
    float xVal;
    float yVal;
    int widthFrame;
    int heightFrame;
    std::vector<BulletObject*> bulletList;
};


#endif