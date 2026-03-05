//
// Created by oto_9 on 06.03.2026.
//
#include "GameRenderer.h"

void GameRenderer::onSurfaceCreated() {
    initGLConfig();
    player = std::make_unique<Player>();
}

void GameRenderer::onDrawFrame() {
    clearBuffers();
    player->onDraw();
}

void GameRenderer::onSurfaceChanged(int width, int height) {

}

void GameRenderer::onDestroy() {

}

