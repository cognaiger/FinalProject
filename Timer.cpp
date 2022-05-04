#include"Timer.h"

Timer::Timer()
{
    startTick = 0;
    pausedTick = 0;
    isPaused = false;
    isStarted = false;
}

Timer::~Timer() 
{

}

void Timer::start() {
    isStarted = true;
    isPaused = false;
    startTick = SDL_GetTicks();
}

void Timer::stop() {
    isPaused = false;
    isStarted = false;
}

void Timer::pause() {
    if (isStarted == true && isPaused == false) {
        isPaused = true;
        pausedTick = SDL_GetTicks() - startTick;
    }
}

void Timer::unpause() {
    if (isPaused == true) {
        isPaused = false;
        startTick = SDL_GetTicks() - pausedTick;
        pausedTick = 0;
    }
}

int Timer::GetTicks() {
    if (isStarted == true) {
        if (isPaused == true) {
            return pausedTick;
        } else {
            return SDL_GetTicks() - startTick;
        }
    }

    return 0;
}

bool Timer::IsStarted() {
    return isStarted;
}

bool Timer::IsPaused() {
    return isPaused;
}