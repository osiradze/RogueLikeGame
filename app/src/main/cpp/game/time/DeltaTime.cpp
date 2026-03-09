//
// Created by oto_9 on 09.03.2026.
//

#include "DeltaTime.h"

float DeltaTime::deltaTime = 0.0f;
std::chrono::high_resolution_clock::time_point DeltaTime::lastTime;

void DeltaTime::update() {
    auto now = std::chrono::high_resolution_clock::now();
    if (lastTime.time_since_epoch().count() != 0) {
        std::chrono::duration<float> elapsed = now - lastTime;
        deltaTime = elapsed.count();
    } else {
        deltaTime = 0.0f;
    }
    lastTime = now;
}

