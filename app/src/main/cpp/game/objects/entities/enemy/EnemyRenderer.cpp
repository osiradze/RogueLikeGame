//
// Created by oto_9 on 11.03.2026.
//

#include <GLES3/gl31.h>
#include "Enemy.h"
#include "utils/OpenglUtils.h"
#include "utils/ShaderUtil.h"
#include "time/DeltaTime.h"

void Enemy::init() {
    if (!data || !data->vertexData) return;

    // init render program
    if (!OpenglUtils::createProgram(shaderProgram, shaders.vertexShader.c_str(),
                                    shaders.fragmentShader.c_str())) { return; }

    // init compute program
    if (!OpenglUtils::createComputeProgram(computeProgram, shaders.computeShader.c_str())) { return; }

    u_camera = glGetUniformLocation(shaderProgram, "u_camera");
    u_point_size = glGetUniformLocation(shaderProgram, "u_point_size");
    initData();
}

void Enemy::initData() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data->vertexDataSize, data->vertexData.get(), GL_DYNAMIC_DRAW);

    // vertex attributes: position (x, y) with stride of 4 floats
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, data->stride, (void *) 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Enemy::runCompute() const {
    ShaderUtil::computeShader(
        computeProgram,
        [this]() {
            auto playerPosition = getPlayerPosition();

            glUniform2f(
                glGetUniformLocation(computeProgram, "u_player_position"),
                playerPosition.x, playerPosition.y
            );
            glUniform1f(
                glGetUniformLocation(computeProgram, "u_delta_time"),
                DeltaTime::deltaTime
            );
            glUniform1ui(
                glGetUniformLocation(computeProgram, "u_enemy_count"),
                static_cast<unsigned int>(enemyCount)
            );
            glUniform1f(
                glGetUniformLocation(computeProgram, "u_collision_radius"),
                radius * 2.0f
            );
            glUniform1ui(
                glGetUniformLocation(computeProgram, "u_floats_per_vertex"),
                static_cast<unsigned int>(numberOfFloatsPerVertex)
            );
        },
        const_cast<unsigned int*>(&vbo),
        1,
        enemyCount, 1, 1
    );
}

void Enemy::draw() const {
    glUseProgram(shaderProgram);
    auto cam = getCameraPosition();
    glUniform2f(u_camera, cam.x, cam.y);
    // radius is in OpenGL units [-1..1], so point size in pixels = radius * screenWidth
    glUniform1f(u_point_size, radius * (float)screenWidth);
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
    glDeleteProgram(computeProgram);
}


