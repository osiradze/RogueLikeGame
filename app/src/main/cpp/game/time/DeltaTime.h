//
// Created by oto_9 on 09.03.2026.
//

#ifndef ROGUELIKE_DELTATIME_H
#define ROGUELIKE_DELTATIME_H

#include <chrono>

class DeltaTime {
public:
    static float deltaTime;
    static int fps;

    static void update();

private:
    static std::chrono::high_resolution_clock::time_point lastTime;
};

#endif //ROGUELIKE_DELTATIME_H
