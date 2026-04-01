//
// Created by oto_9 on 31.03.2026.
//

#include <GLES3/gl31.h>
#include <android/log.h>
#include "Bullets.h"
#include "utils/OpenglUtils.h"
#include "utils/ShaderUtil.h"
#include "time/DeltaTime.h"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)


void Bullets::initRender() {
    __android_log_print(ANDROID_LOG_DEBUG, "Bullets", "Start");

    if (!data || !data->vertexData) return;

    // init render program
    if (!OpenglUtils::createProgram(shaderProgram, shaders.vertexShader.c_str(),shaders.fragmentShader.c_str())) { return; }
    // init compute program
    if (!OpenglUtils::createComputeProgram(computeProgram, shaders.computeShader.c_str())) { return; }

    initUniforms();
    initData();
    data.reset();
    __android_log_print(ANDROID_LOG_DEBUG, "Bullets", "Success");
}

void Bullets::initUniforms() {
    // render uniforms
    renderUniforms.u_camera     = glGetUniformLocation(shaderProgram, "u_camera");
    renderUniforms.u_point_size = glGetUniformLocation(shaderProgram, "u_point_size");

    computeUniforms.u_delta_time        = glGetUniformLocation(computeProgram, "u_delta_time");
    computeUniforms.u_floats_per_vertex = glGetUniformLocation(computeProgram, "u_floats_per_vertex");

    glUseProgram(computeProgram);
    glUniform1ui(computeUniforms.u_floats_per_vertex, static_cast<unsigned int>(properties.numberOfFloatsPerVertex));
    glUseProgram(0);


}

void Bullets::initData() {
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
