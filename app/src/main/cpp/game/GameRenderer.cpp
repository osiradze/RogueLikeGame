//
// Created by oto_9 on 06.03.2026.
//
#include "GameRenderer.h"

void GameRenderer::onSurfaceCreated() {
    initGLConfig();
    reader = std::make_unique<SSBOReader>();
    camera = std::make_unique<Camera>();
    player = std::make_unique<Player>(
            camera->getPositionFunction()
    );
    camera->setPlayerPositionFunction(
            player->getPositionFunction()
    );
    player->init();

    bullets = std::make_unique<Bullets>(
            camera->getPositionFunction()
    );

    enemy = std::make_unique<Enemy>(
            player.get(),
            camera->getPositionFunction(),
            reader.get()
    );
    enemy->init();
    reader->init();
    bullets->init();

    enemy->setBulletsApi(
        bullets->getApi()
    );
}

void GameRenderer::onDrawFrame() {
    clearBuffers();
    camera->update();
    bullets->update();
    enemy->update();
    player->update();


    if (++frameCount >= readInterval) {
        frameCount = 0;
        reader->read();
    }
}

void GameRenderer::onSurfaceChanged(int width, int height) {
    player->setRatio((float) height / (float) width);
    enemy->setScreenWidth(width);
    bullets->setScreenWidth(width);
}

void GameRenderer::onDestroy() {
    player->destroy();
    enemy->destroy();
    reader->destroy();
    bullets->destroy();
}

void GameRenderer::onMove(Move move) {
    player->onMove(move);
}

void GameRenderer::onUp() {
    player->onUp();
}
