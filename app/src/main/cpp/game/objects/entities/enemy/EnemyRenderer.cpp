//
// Created by oto_9 on 11.03.2026.
//

#include <GLES3/gl31.h>
#include "Enemy.h"
#include "utils/OpenglUtils.h"

void Enemy::init() {
    if (!data || !data->vertexData) return;

    // init programs
    if (!OpenglUtils::createProgram(shaderProgram, shaders.vertexShader.c_str(),
                                    shaders.fragmentShader.c_str())) { return; }
    initData();
}

void Enemy::initData() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data->vertexDataSize, data->vertexData.get(), GL_DYNAMIC_DRAW);

    // vertex attributes
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, data->stride, (void *) 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}



void Enemy::draw() const {
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glDrawArrays(GL_POINTS, 0, enemyCount);
    glBindVertexArray(0);
    glUseProgram(0);
}

void Enemy::destroy() {
    glBindVertexArray(0);
    glUseProgram(0);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shaderProgram);
}
