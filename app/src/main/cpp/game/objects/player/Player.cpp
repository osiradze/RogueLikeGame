//
// Created by oto_9 on 06.03.2026.
//
#include "Player.h"
#include "../../utils/OpenglUtils.h"
#include <GLES3/gl31.h>


void Player::init() {
    renderer.init();
}

void Player::update() {
    translation.move(velocity * 0.1f);
    velocity += direction;
    if(glm::length(velocity) > 0.1f) {
        velocity = glm::normalize(velocity) * 0.1f;
    }
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
    float scale = 0.005;
    direction = glm::vec2(x * scale , -y * scale);
}

void Player::onUp() {
    direction = glm::vec2(0, 0);
}
