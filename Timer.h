#ifndef TIMER_H
#define TIMER_H

#include"base.h"

// handle the time of the game (fps)
class Timer {
public:
    Timer();
    ~Timer();

    // start program = true and mark time
    void start();

    // stop program
    void stop();

    // pause program = true and mark time
    void pause();

    // pause program = false
    void unpause();

    // if program is paused then get pauseTime, else get current time
    int GetTicks();

    // return whether program has started
    bool IsStarted();

    // return whether program is paused
    bool IsPaused();

private:
    int startTick;
    int pausedTick;

    bool isPaused;
    bool isStarted;
};

#endif
