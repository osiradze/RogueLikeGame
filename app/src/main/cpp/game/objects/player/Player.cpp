//
// Created by oto_9 on 06.03.2026.
//
#include "Player.h"
#include "../../utils/OpenglUtils.h"
#include <GLES3/gl31.h>
#include "../../time/DeltaTime.h"


void Player::init() {
    renderer.init();
}

void Player::update() {
    translation.move(velocity * DeltaTime::deltaTime);
    velocity += direction * speed;
    velocity *= 0.90;
    renderer.draw();
}

void Player::setRatio(float ratio) {
    translation.setRatio(ratio);
}

void Player::destroy() {
    renderer.destroy();
}

void Player::onMove(float x, float y) {
    direction = glm::vec2(x, -y);
}

void Player::onUp() {
    direction = glm::vec2(0, 0);
}
