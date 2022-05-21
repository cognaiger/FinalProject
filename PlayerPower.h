#ifndef PLAYER_POWER_H
#define PLAYER_POWER_H

#include"base.h"
#include"BaseObject.h"

// represent health image player have
class PlayerPower : public BaseObject
{
public:
    PlayerPower();
    ~PlayerPower();

    void SetNum(const int& num) { number = num; }
    void AddPos(const int& xPos);

    // base on element in posList to show on renderer
    void Show(SDL_Renderer* screen);

    // init 3 health, image and position
    void Init(SDL_Renderer* screen);

    void Increase();
    void Decrease();

private:
    int number;
    // position(x) where image is displayed
    std::vector<int> posList;
};


class PlayerMoney : public BaseObject
{
public:
    PlayerMoney();
    ~PlayerMoney();

    // load image money
    bool Init(SDL_Renderer* screen);

    // show image on renderer
    void Show(SDL_Renderer* screen);
    void SetPos(const int& xp, const int& yp) { xPos = xp; yPos = yp; }

private:
    int xPos;
    int yPos;
};


#endif 