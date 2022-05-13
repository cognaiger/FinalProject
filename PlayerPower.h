#ifndef PLAYER_POWER_H
#define PLAYER_POWER_H

#include"base.h"
#include"BaseObject.h"

class PlayerPower : public BaseObject
{
public:
    PlayerPower();
    ~PlayerPower();

    void SetNum(const int& num) { number = num; }
    void AddPos(const int& xPos);
    void Show(SDL_Renderer* screen);
    void Init(SDL_Renderer* screen);

    void Increase();
    void Decrease();

private:
    int number;
    std::vector<int> posList;
};


class PlayerMoney : public BaseObject
{
public:
    PlayerMoney();
    ~PlayerMoney();

    bool Init(SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
    void SetPos(const int& xp, const int& yp) { xPos = xp; yPos = yp; }

private:
    int xPos;
    int yPos;
};


#endif 