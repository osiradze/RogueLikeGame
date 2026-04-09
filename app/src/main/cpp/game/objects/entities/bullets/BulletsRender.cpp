//
// Created by oto_9 on 31.03.2026.
//

#include <GLES3/gl31.h>
#include <android/log.h>
#include "Bullets.h"
#include "utils/OpenglUtils.h"
#include "utils/ShaderUtil.h"
#include "time/DeltaTime.h"


void Bullets::initRender() {

    if (!data || !data->vertexData) return;

    // init render program
    if (!OpenglUtils::createProgram(shaderProgram, shaders.vertexShader.c_str(), shaders.fragmentShader.c_str())) { return; }
    // init update compute program
    if (!OpenglUtils::createComputeProgram(computeProgram, shaders.computeShader.c_str())) { return; }
    // init spawn compute program
    if (!OpenglUtils::createComputeProgram(spawnProgram, spawnShaderPath.c_str())) { return; }

    initUniforms();
    initData();
    data.reset();
}

void Bullets::initUniforms() {
    // render uniforms
    renderUniforms.u_camera     = glGetUniformLocation(shaderProgram, "u_camera");
    renderUniforms.u_point_size = glGetUniformLocation(shaderProgram, "u_point_size");

    // update compute uniforms
    computeUniforms.u_delta_time        = glGetUniformLocation(computeProgram, "u_delta_time");
    computeUniforms.u_floats_per_vertex = glGetUniformLocation(computeProgram, "u_floats_per_vertex");
    bulletUniforms.u_bullet_speed      = glGetUniformLocation(computeProgram, "u_bullet_speed");

    glUseProgram(computeProgram);
    glUniform1ui(computeUniforms.u_floats_per_vertex, static_cast<unsigned int>(properties.numberOfFloatsPerVertex));
    glUniform1f(bulletUniforms.u_bullet_speed, properties.bulletSpeed);
    glUseProgram(0);

    // spawn compute uniforms
    bulletUniforms.u_spawn_position    = glGetUniformLocation(spawnProgram, "u_spawn_position");
    bulletUniforms.u_spawn_direction   = glGetUniformLocation(spawnProgram, "u_spawn_direction");
    bulletUniforms.u_floats_per_vertex = glGetUniformLocation(spawnProgram, "u_floats_per_vertex");
    bulletUniforms.u_bullet_count      = glGetUniformLocation(spawnProgram, "u_bullet_count");

    glUseProgram(spawnProgram);
    glUniform1ui(bulletUniforms.u_floats_per_vertex, static_cast<unsigned int>(properties.numberOfFloatsPerVertex));
    glUniform1ui(bulletUniforms.u_bullet_count, static_cast<unsigned int>(properties.maxBullets));
    glUseProgram(0);
}

void Bullets::initData() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data->vertexDataSize, data->vertexData.get(), GL_DYNAMIC_DRAW);

    // vertex attributes: position (x, y), velocity (x, y), color (r, g, b), isAlive, lifetime
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, properties.numberOfFloatsPerVertex * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, properties.numberOfFloatsPerVertex * sizeof(float), (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, properties.numberOfFloatsPerVertex * sizeof(float), (void *)(4 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, properties.numberOfFloatsPerVertex * sizeof(float), (void *)(7 * sizeof(float)));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Bullets::runCompute() {
    unsigned int ssbos[] = { vbo };
    ShaderUtil::computeShader(
            computeProgram,
            [this]() {
                glUniform1f(computeUniforms.u_delta_time, DeltaTime::deltaTime);
            },
            ssbos,
            1,
            properties.maxBullets, 1, 1
    );
}

void Bullets::spawn(glm::vec2 position, glm::vec2 direction) {
    unsigned int ssbos[] = { vbo };
    ShaderUtil::computeShader(
            spawnProgram,
            [this, position, direction]() {
                glUniform2f(bulletUniforms.u_spawn_position, position.x, position.y);
                glUniform2f(bulletUniforms.u_spawn_direction, direction.x, direction.y);
            },
            ssbos,
            1,
            1, 1, 1   // single workgroup — shader loops over all bullets
    );
}

void Bullets::draw() const {
    glUseProgram(shaderProgram);
    auto cam = getCameraPosition();
    glUniform2f(renderUniforms.u_camera, cam.x, cam.y);
    glUniform1f(renderUniforms.u_point_size, properties.bulletRadius * (float)screenWidth);
    glBindVertexArray(vao);
    glDrawArrays(GL_POINTS, 0, properties.maxBullets);
    glBindVertexArray(0);
    glUseProgram(0);
}

void Bullets::destroy() {
    glBindVertexArray(0);
    glUseProgram(0);
    glDeleteVertexArrays(1, &vao);
}
