#include "utils/OpenglUtils.h"
#include "LineRenderer.h"
#include <GLES3/gl31.h>
//
// Created by oto_9 on 08.03.2026.
//
void LineRenderer::init() {
    if (!data || !data->vertexData) return;

    // init programs
    if (!OpenglUtils::createProgram(shaderProgram, shaders.vertexShader.c_str(),
                                    shaders.fragmentShader.c_str())) { return; }
    uniforms.u_camera = glGetUniformLocation(shaderProgram, "u_camera");
    uniforms.u_ratio  = glGetUniformLocation(shaderProgram, "u_ratio");
    initData();
}

void LineRenderer::initData() {
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

void LineRenderer::draw() {
    glUseProgram(shaderProgram);
    updateData();
    glBindVertexArray(vao);
    glDrawArrays(GL_LINES, 0, 2);
    glBindVertexArray(0);
    glUseProgram(0);
}

void LineRenderer::updateData() {
    glm::vec3 playerPos = getPlayerPosition();
    glm::vec3 aimPos = getAimPosition();

    auto stepX = (aimPos.x - playerPos.x) / 10;
    auto stepY = (aimPos.y - playerPos.y) / 10;

    data->vertexData[0] = playerPos.x - stepX;
    data->vertexData[1] = playerPos.y - stepY;
    data->vertexData[2] = playerPos.x + 2 * stepX;
    data->vertexData[3] = playerPos.y + 2 * stepY;

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, data->vertexDataSize, data->vertexData.get());
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    auto cam = getCameraPosition();
    glUniform2f(uniforms.u_camera, cam.x, cam.y);
    glUniform1f(uniforms.u_ratio, ratio);
}

void LineRenderer::destroy() {
    glBindVertexArray(0);
    glUseProgram(0);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shaderProgram);
}

void LineRenderer::setRatio(float r) {
    ratio = r;
    glUseProgram(shaderProgram);
    glUniform1f(uniforms.u_ratio, ratio);
    glUseProgram(0);
}
