//
// Created by oto_9 on 06.03.2026.
//
#include "GameRenderer.h"

void GameRenderer::onSurfaceCreated() {
    initGLConfig();
    player = std::make_unique<Player>();
    player->init();
    enemy = std::make_unique<Enemy>();
    enemy->init();
}

void GameRenderer::onDrawFrame() {
    clearBuffers();
    player->update();
    enemy->update();
}

void GameRenderer::onSurfaceChanged(int width, int height) {
    player->setRatio((float) height / (float) width);
}

void GameRenderer::onDestroy() {
    player->destroy();
    enemy->destroy();
}

void GameRenderer::onMove(Move move) {
    player->onMove(move);
}

void GameRenderer::onUp() {
    player->onUp();
}

