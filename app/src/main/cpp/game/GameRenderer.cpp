//
// Created by oto_9 on 06.03.2026.
//
#include "GameRenderer.h"

void GameRenderer::onSurfaceCreated() {
    initGLConfig();
    camera = std::make_unique<Camera>();
    player = std::make_unique<Player>(camera->getPositionFunction());
    camera->setPlayerPositionFunction(player->getPositionFunction());
    player->init();

    enemy = std::make_unique<Enemy>(player->getPositionFunction(), camera->getPositionFunction());
    enemy->init();
}

void GameRenderer::onDrawFrame() {
    clearBuffers();
    player->update();
    enemy->update();
    camera->update();
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

