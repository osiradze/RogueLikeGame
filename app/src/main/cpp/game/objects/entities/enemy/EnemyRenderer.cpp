//
// Created by oto_9 on 11.03.2026.
//

#include <GLES3/gl31.h>
#include <android/log.h>
#include "Enemy.h"
#include "utils/OpenglUtils.h"
#include "utils/ShaderUtil.h"
#include "time/DeltaTime.h"
#include "vbo/ISSBOBuffer.h"

#define LOG_TAG "EnemyDebug"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

void Enemy::initRender() {
    if (!data || !data->vertexData) return;

    // init render program
    if (!OpenglUtils::createProgram(shaderProgram, shaders.vertexShader.c_str(),shaders.fragmentShader.c_str())) { return; }
    // init compute program
    if (!OpenglUtils::createComputeProgram(computeProgram, shaders.computeShader.c_str())) { return; }

    initUniforms();
    initData();
    data.reset();
}

void Enemy::initUniforms() {
    // render uniforms
    renderUniforms.u_camera     = glGetUniformLocation(shaderProgram, "u_camera");
    renderUniforms.u_point_size = glGetUniformLocation(shaderProgram, "u_point_size");

    // compute uniforms
    computeUniforms.u_player_position   = glGetUniformLocation(computeProgram, "u_player_position");
    computeUniforms.u_delta_time        = glGetUniformLocation(computeProgram, "u_delta_time");
    computeUniforms.u_enemy_count       = glGetUniformLocation(computeProgram, "u_enemy_count");
    computeUniforms.u_collision_radius  = glGetUniformLocation(computeProgram, "u_collision_radius");
    computeUniforms.u_floats_per_vertex = glGetUniformLocation(computeProgram, "u_floats_per_vertex");
    computeUniforms.u_bounds            = glGetUniformLocation(computeProgram, "u_bounds");

    glUseProgram(computeProgram);
    glUniform1ui(computeUniforms.u_enemy_count, static_cast<unsigned int>(properties.enemyCount));
    glUniform1f(computeUniforms.u_collision_radius, properties.radius * 2.0f);
    glUniform1ui(computeUniforms.u_floats_per_vertex, static_cast<unsigned int>(properties.numberOfFloatsPerVertex));
    glUniform4f(computeUniforms.u_bounds, spawnBounds.x, spawnBounds.y, spawnBounds.z, spawnBounds.w);
    glUseProgram(0);
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

void Enemy::runCompute() {
    unsigned int ssbos[] = { vbo, reader->getSSBO() };
    ShaderUtil::computeShader(
        computeProgram,
        [this]() {
            auto playerPosition = getPlayerPosition();
            glUniform2f(computeUniforms.u_player_position, playerPosition.x, playerPosition.y);
            glUniform1f(computeUniforms.u_delta_time, DeltaTime::deltaTime);
        },
        ssbos,
        2,
        properties.enemyCount, 1, 1
    );
}

void Enemy::draw() const {
    glUseProgram(shaderProgram);
    auto cam = getCameraPosition();
    glUniform2f(renderUniforms.u_camera, cam.x, cam.y);
    glUniform1f(renderUniforms.u_point_size, properties.radius * (float)properties.screenWidth);
    glBindVertexArray(vao);
    glDrawArrays(GL_POINTS, 0, properties.enemyCount);
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


