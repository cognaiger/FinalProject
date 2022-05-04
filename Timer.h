#ifndef TIMER_H
#define TIMER_H

#include"base.h"

class Timer {
public:
    Timer();
    ~Timer();

    void start();
    void stop();
    void pause();
    void unpause();

    int GetTicks();

    bool IsStarted();
    bool IsPaused();

private:
    int startTick;
    int pausedTick;

    bool isPaused;
    bool isStarted;
};

#endif
