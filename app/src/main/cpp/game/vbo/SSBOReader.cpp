//
// Created by oto_9 on 18.03.2026.
//
#include <GLES3/gl31.h>
#include "SSBOReader.h"

unsigned int SSBOReader::ssbo = 0;


SSBOReader::SSBOReader() {
    // Create debug SSBO (4 floats)
    glGenBuffers(1, &ssbo);
    writeCleanData();

}

void SSBOReader::read() {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    delete readData;
    readData = (float*)glMapBufferRange(
            GL_SHADER_STORAGE_BUFFER, 0,
            SIZE * sizeof(float),
            GL_MAP_READ_BIT
    );
    writeCleanData();
}

void SSBOReader::writeCleanData() {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(cleanData), cleanData, GL_DYNAMIC_READ);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

