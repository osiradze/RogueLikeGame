#include "../../utils/OpenglUtils.h"
#include "PlayerRenderer.h"
#include <GLES3/gl31.h>
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
    initTexture();
}

void PlayerRenderer::initUniforms() {
    u_model = glGetUniformLocation(shaderProgram, "u_model");
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

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data->indicesSize, data->indices.get(),
                 GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void PlayerRenderer::initTexture() {

}

void PlayerRenderer::draw() {
    glUseProgram(shaderProgram);
    updateUniforms();
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, data->indicesCount, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
    glUseProgram(0);
}

void PlayerRenderer::updateUniforms() {
    glUniformMatrix4fv(u_model, 1, GL_FALSE, &getModel()[0][0]); // [0][0] because we want pointer of the first number
}

void PlayerRenderer::destroy() {
    glBindVertexArray(0);
    glUseProgram(0);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteProgram(shaderProgram);
}
