#include"PlayerPower.h"

PlayerPower::PlayerPower() {
    number = 0;
}

PlayerPower::~PlayerPower() {

}

void PlayerPower::AddPos(const int& xPos) {
    posList.push_back(xPos);
}

void PlayerPower::Init(SDL_Renderer* screen) {
    LoadImg("img/player_pw.png", screen);
    number = 3;
    if (posList.size() > 0) {
        posList.clear();
    }

    AddPos(20);
    AddPos(60);
    AddPos(100);
}

void PlayerPower::Show(SDL_Renderer* screen) {
    for (int i = 0; i < posList.size(); i++) {
        rect.x = posList[i];
        rect.y = 0;
        Render(screen);
    }
}

void PlayerPower::Decrease() {
    number--;
    posList.pop_back();
}

void PlayerPower::Increase() {
    number++;
    int lastPos = posList.back();
    lastPos += 40;
    posList.push_back(lastPos);
}



PlayerMoney::PlayerMoney() {
    xPos = 0;
    yPos = 0;
}

PlayerMoney::~PlayerMoney() {

}

bool PlayerMoney::Init(SDL_Renderer* screen) {
    bool ret = LoadImg("img/money_img.png", screen);
    return ret;
}

void PlayerMoney::Show(SDL_Renderer* screen) {
    rect.x = xPos;
    rect.y = yPos;
    Render(screen);
}