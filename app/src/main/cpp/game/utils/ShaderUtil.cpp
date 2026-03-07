//
// Created by OSiradze on 28.08.25.
//
#include "ShaderUtil.h"
#include <GLES3/gl31.h>


void ShaderUtil::computeShader(unsigned int shaderProgram,
                               const std::function<void()> &uniforms,
                               unsigned int* vbos,
                               unsigned int vboCount,
                               int x, int y, int z) {
    glUseProgram(shaderProgram);

    // Bind SSBOs to consecutive binding points (0..n-1)
    for (GLuint index = 0; index < vboCount; ++index) {
        // glBindBuffer is not required before glBindBufferBase, but harmless:
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, vbos[index]);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, vbos[index]);
    }

    // Set uniforms (if any)
    if (uniforms) uniforms();

    // Dispatch
    glDispatchCompute(x, y, z);

    // Ensure writes are visible before subsequent use (tweak bits as needed)
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

    glUseProgram(0);
}

