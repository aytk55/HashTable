// Timer.h

#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer {
public:
    Timer();
    void start();
    void stop();
    double elapsed();

private:
    bool isRunning;
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime, endTime;
};

#endif // TIMER_H
