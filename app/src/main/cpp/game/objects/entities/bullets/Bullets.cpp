//
// Created by oto_9 on 31.03.2026.
//
#include "Bullets.h"

std::unique_ptr<float[]> Bullets::getData() const {
    auto size = properties.maxBullets * properties.numberOfFloatsPerVertex;
    auto buffer = std::make_unique<float[]>(size);
    std::fill(buffer.get(), buffer.get() + size, 0.0f);
    return buffer;
}

void Bullets::init() {
    initRender();
}

void Bullets::update() {
    runCompute();
    draw();
    //handleReadData(reader->getData(name));
}