//
// Created by oto_9 on 10.03.2026.
//
#include "Enemy.h"
#include "utils/OpenglUtils.h"
#include <random>

std::unique_ptr<float[]> Enemy::getData() const {
    auto buffer = std::make_unique<float[]>(enemyCount * numberOfFloatsPerVertex);

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(-1, 1);

    for (int i = 0; i < enemyCount; i++) {
        int offset = i * numberOfFloatsPerVertex;
        buffer[offset + 0] = dist(rng); // x
        buffer[offset + 1] = dist(rng); // y
        buffer[offset + 2] = 0.0f;      // vx
        buffer[offset + 3] = 0.0f;      // vy
    }

    return buffer;
}

void Enemy::update() {
    draw();
}