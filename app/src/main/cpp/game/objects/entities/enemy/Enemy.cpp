//
// Created by oto_9 on 10.03.2026.
//
#include "Enemy.h"
#include "utils/OpenglUtils.h"
#include <random>

std::unique_ptr<float[]> Enemy::getData() const {
    auto buffer = std::make_unique<float[]>(properties.enemyCount * properties.numberOfFloatsPerVertex);

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> distX(spawnBounds.x, spawnBounds.z);
    std::uniform_real_distribution<float> distY(spawnBounds.y, spawnBounds.w);
    std::uniform_real_distribution<float> distColor(0.0f, 1.0f);

    for (int i = 0; i < properties.enemyCount; i++) {
        int offset = i * properties.numberOfFloatsPerVertex;
        buffer[offset + 0] = distX(rng); // x
        buffer[offset + 1] = distY(rng); // y
        buffer[offset + 2] = 0.0f;      // vx
        buffer[offset + 3] = 0.0f;      // vy
        buffer[offset + 4] = 1.0f;      // stopper
        buffer[offset + 5] = 0.0f;      // i
        buffer[offset + 6] = distColor(rng); // r
        buffer[offset + 7] = distColor(rng); // g
        buffer[offset + 8] = distColor(rng); // b
    }

    return buffer;
}

void Enemy::init() {
    ssboOffset = reader->allocate(name, readSize);
    initRender();
}

void Enemy::update() {
    runCompute();
    draw();
    //handleReadData(reader->getData(name));
}

void Enemy::handleReadData(std::vector<float> data){
    // Do some things
}
