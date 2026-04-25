#include "utils/OpenglUtils.h"
#include "PlayerRenderer.h"
#include <GLES3/gl31.h>
#include "time/DeltaTime.h"
#include <glm/gtc/matrix_transform.hpp>
//
// Created by oto_9 on 08.03.2026.
//
void PlayerRenderer::init() {
    if (!data || !data->vertexData || !data->indices) return;

    // init programs
    if (!OpenglUtils::createProgram(shaderProgram, shaders.vertexShader.c_str(),
                                    shaders.fragmentShader.c_str())) { return; }
    initUniforms();
    initData();
}

void PlayerRenderer::initUniforms() {
    uniforms.u_model  = glGetUniformLocation(shaderProgram, "u_model");
    uniforms.u_camera = glGetUniformLocation(shaderProgram, "u_camera");
    uniforms.u_time   = glGetUniformLocation(shaderProgram, "u_time");
    uniforms.u_alpha  = glGetUniformLocation(shaderProgram, "u_alpha");
    uniforms.u_glow   = glGetUniformLocation(shaderProgram, "u_glow");
}

void PlayerRenderer::initData() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data->vertexDataSize, data->vertexData.get(), GL_STATIC_DRAW);

    // vertex attributes
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, data->stride, (void *) 0);
    glEnableVertexAttribArray(0);

    // uv attributes
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, data->stride, (void *) (2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data->indicesSize, data->indices.get(),
                 GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void PlayerRenderer::draw() {
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    updateUniforms();
    drawGlow();
    drawPlayer();
    glBindVertexArray(0);
    glUseProgram(0);
}

void PlayerRenderer::drawGlow() {
    glm::mat4 glowModel = glm::scale(getModel(), glm::vec3(2.0f, 2.0f, 1.0f));
    glUniformMatrix4fv(uniforms.u_model, 1, GL_FALSE, &glowModel[0][0]);
    glUniform1f(uniforms.u_alpha, 0.1f);
    glUniform1i(uniforms.u_glow, 1);
    glDrawElements(GL_TRIANGLES, data->indicesCount, GL_UNSIGNED_INT, nullptr);
}

void PlayerRenderer::drawPlayer() {
    glUniformMatrix4fv(uniforms.u_model, 1, GL_FALSE, &getModel()[0][0]);
    glUniform1f(uniforms.u_alpha, 1.0f);
    glUniform1i(uniforms.u_glow, 0);
    glDrawElements(GL_TRIANGLES, data->indicesCount, GL_UNSIGNED_INT, nullptr);
}

void PlayerRenderer::updateUniforms() {
    auto cam = getCameraPosition();
    glUniform2f(uniforms.u_camera, cam.x, cam.y);
    glUniform1f(uniforms.u_time, DeltaTime::totalTime);
}

void PlayerRenderer::destroy() {
    glBindVertexArray(0);
    glUseProgram(0);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteProgram(shaderProgram);
}
