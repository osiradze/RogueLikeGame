//
// Created by oto_9 on 06.03.2026.
//
#include "GameRenderer.h"

void GameRenderer::onSurfaceCreated() {
    initGLConfig();
    player = std::make_unique<Player>();
    player->init();
}

void GameRenderer::onDrawFrame() {
    clearBuffers();
    player->update();
}

void GameRenderer::onSurfaceChanged(int width, int height) {
    player->setRatio((float) height / (float) width);
}

void GameRenderer::onDestroy() {
    player->destroy();
}

