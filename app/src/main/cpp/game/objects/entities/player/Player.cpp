//
// Created by oto_9 on 06.03.2026.
//
#include "Player.h"
#include "utils/OpenglUtils.h"
#include <GLES3/gl31.h>
#include "time/DeltaTime.h"

void Player::init() {
    playerRenderer.init();
    aimRenderer.init();
    lineRenderer.init();
}

void Player::update() {
    playerTranslation.move(velocity * DeltaTime::deltaTime);
    velocity += direction * speed;
    velocity *= 0.90;
    aimTranslation.setPosition(playerTranslation.getPosition() + aimDirection);

    playerRenderer.draw();
    aimRenderer.draw();
    lineRenderer.draw();
}

void Player::setRatio(float ratio) {
    playerTranslation.setRatio(ratio);
    aimTranslation.setRatio(ratio);
}

void Player::destroy() {
    playerRenderer.destroy();
    aimRenderer.destroy();
    lineRenderer.destroy();
}

void Player::onMove(Move move) {
    if(move.cNumber == 0){
        direction = glm::vec3(move.x, -move.y, 0);
    } else if(move.cNumber == 1) {
        aimDirection = glm::normalize( glm::vec3(move.x, -move.y, 0)) * maxAimDistance;
        aimDirection.x *= aimTranslation.getRatio();
    }

}

void Player::onUp() {
    direction = glm::vec3(0);
}
