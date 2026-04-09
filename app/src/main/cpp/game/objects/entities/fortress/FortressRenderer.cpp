#include <android/log.h>
#include <GLES3/gl31.h>
#include "Fortress.h"
#include "utils/OpenglUtils.h"

//
// Created by oto_9 on 09.04.2026.
//
void Fortress::initRender() {
    if (!data || !data->vertexData) return;

    // init render program
    if (!OpenglUtils::createProgram(shaderProgram, shaders.vertexShader.c_str(), shaders.fragmentShader.c_str())) { return; }
   /* // init update compute program
    if (!OpenglUtils::createComputeProgram(computeProgram, shaders.computeShader.c_str())) { return; }*/

    initUniforms();
    initRenderData();
    data.reset();
}

void Fortress::initUniforms() {
    // render uniforms
    renderUniforms.u_camera     = glGetUniformLocation(shaderProgram, "u_camera");
    renderUniforms.u_point_size = glGetUniformLocation(shaderProgram, "u_point_size");
}

void Fortress::initRenderData() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data->vertexDataSize, data->vertexData.get(), GL_DYNAMIC_DRAW);

    // vertex attributes: position (x, y), velocity (x, y), color (r, g, b)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, properties.numberOfFloatsPerVertex * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, properties.numberOfFloatsPerVertex * sizeof(float), (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, properties.numberOfFloatsPerVertex * sizeof(float), (void *)(4 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Fortress::draw() const {
    glUseProgram(shaderProgram);
    auto cam = getCameraPosition();
    glUniform2f(renderUniforms.u_camera, cam.x, cam.y);
    glUniform1f(renderUniforms.u_point_size, properties.pointRadius * (float)screenWidth);
    glBindVertexArray(vao);
    glDrawArrays(GL_POINTS, 0, properties.pointCount);
    glBindVertexArray(0);
    glUseProgram(0);
}

void Fortress::destroy() {
    glBindVertexArray(0);
    glUseProgram(0);
    glDeleteVertexArrays(1, &vao);
}

void Fortress::setRatio(float r) {
    ratio = r;
}

