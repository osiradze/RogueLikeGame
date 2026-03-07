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
    translation.move(velocity * 0.01f);
    velocity += acceleration;
    renderer.draw();
}

void Player::setRatio(float ratio) {
    translation.setRatio(ratio);
}

void Player::destroy() {
    renderer.destroy();
}
