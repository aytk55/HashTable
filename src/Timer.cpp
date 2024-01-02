// Timer.cpp

#include "../headers/Timer.h"

Timer::Timer() : isRunning(false) {}


void Timer::start() {
    isRunning = true;
    startTime = std::chrono::high_resolution_clock::now();
}

void Timer::stop() {
    isRunning = false;
    endTime = std::chrono::high_resolution_clock::now();
}

double Timer::elapsed() {
    std::chrono::time_point<std::chrono::high_resolution_clock> endTimePoint = isRunning ? std::chrono::high_resolution_clock::now() : endTime;
    std::chrono::duration<double, std::milli> duration = endTimePoint - startTime;
    return duration.count();
}
