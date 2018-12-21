#pragma once

#include <chrono>

class Timer {
public:
    static void start();

    static long stop();

private:
    static std::chrono::high_resolution_clock::time_point begin;
    static std::chrono::high_resolution_clock::time_point end;
};


