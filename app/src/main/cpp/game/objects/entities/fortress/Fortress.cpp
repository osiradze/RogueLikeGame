//
// Created by oto_9 on 07.04.2026.
//
#include "Fortress.h"
#include <random>

void Fortress::init() {
    importImage();

    std::mt19937 rng(std::random_device{}());
    int rx = std::uniform_int_distribution<int>(0, properties.divisionX - 1)(rng);
    int ry = std::uniform_int_distribution<int>(0, properties.divisionY - 1)(rng);

    fortressSprite = getSelectedRect(rx, ry);
    generatePoints();
    initData();
    initRender();
}

void Fortress::update() {
    draw();
}
