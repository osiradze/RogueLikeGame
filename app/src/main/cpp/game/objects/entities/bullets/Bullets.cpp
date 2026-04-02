//
// Created by oto_9 on 31.03.2026.
//
#include "Bullets.h"
#include <random>
#include <cmath>

std::unique_ptr<float[]> Bullets::getData() const {
    auto size = properties.maxBullets * properties.numberOfFloatsPerVertex;
    auto buffer = std::make_unique<float[]>(size);

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> angleDist(0.0f, 2.0f * M_PI);

    for (int i = 0; i < properties.maxBullets; i++) {
        int offset = i * properties.numberOfFloatsPerVertex;
        float angle = angleDist(rng);
        buffer[offset + 0] = 0.0f;            // x
        buffer[offset + 1] = 0.0f;            // y
        buffer[offset + 2] = 0.0;             // vx (normalized direction)
        buffer[offset + 3] = 0.0;             // vy (normalized direction)
        buffer[offset + 4] = 1.0f;            // r
        buffer[offset + 5] = 1.0f;            // g
        buffer[offset + 6] = 1.0f;            // b
        buffer[offset + 7] = 0.0f;            // isAlive
        buffer[offset + 8] = 0.0f;            // lifetime
    }

    return buffer;
}

void Bullets::init() {
    initRender();
}

void Bullets::update() {
    runCompute();
    draw();
}