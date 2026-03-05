//
// Created by oto_9 on 06.03.2026.
//
#include "Player.h"

void Player::init() {

}

void Player::onDraw() {
    velocity += acceleration;
    position += velocity;
}

void Player::destroy() {

}