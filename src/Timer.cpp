#include "Timer.h"

std::chrono::high_resolution_clock::time_point Timer::begin;
std::chrono::high_resolution_clock::time_point Timer::end;

void Timer::start() {
    begin = std::chrono::high_resolution_clock::now();
}

long Timer::stop() {
    end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
}
