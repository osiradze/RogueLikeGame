//
// Created by oto_9 on 06.03.2026.
//
#include "Player.h"
#include "../../utils/OpenglUtils.h"

void Player::init() {
    if (!data || !data->vertexData || !data->indices) return;

    // init programs
    if (!OpenglUtils::createProgram(shaderProgram, shaders.vertexShader.c_str(),
                                    shaders.fragmentShader.c_str())) { return; }
    initUniforms();
    initData();
    initTexture();
}

void Player::onDraw() {

}

void Player::destroy() {

}


void Player::initUniforms() {

}

void Player::initData() {

}

void Player::initTexture() {

}
