//
// Created by oto_9 on 18.03.2026.
//
#include <GLES3/gl31.h>
#include <cstring>
#include "SSBOReader.h"

SSBOReader::SSBOReader() {
    glGenBuffers(1, &ssbo);
}

unsigned int SSBOReader::allocate(const std::string& key, int length) {
    unsigned int offset = size;
    buffers[key] = std::make_pair(offset, length);
    size += length;
    return offset;
}

void SSBOReader::init() {
    delete[] cleanData;
    cleanData = new float[size]();
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, size * sizeof(float), cleanData, GL_DYNAMIC_READ);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void SSBOReader::read() {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);

    float* mapped = (float*)glMapBufferRange(
            GL_SHADER_STORAGE_BUFFER, 0,
            size * sizeof(float),
            GL_MAP_READ_BIT
    );

    delete[] readData;
    readData = nullptr;

    if (mapped) {
        readData = new float[size];
        memcpy(readData, mapped, size * sizeof(float));
        glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
    }

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    // reset SSBO to zeros for the next frame
    init();
}

std::vector<float> SSBOReader::getData(const std::string& key) {
    auto it = buffers.find(key);
    if (it == buffers.end() || readData == nullptr) {
        return {};
    }

    unsigned int offset = it->second.first;
    unsigned int size   = it->second.second;

    return {readData + offset, readData + offset + size};
}

void SSBOReader::destroy() {
    glDeleteBuffers(1, &ssbo);
    delete[] cleanData;
    cleanData = nullptr;
    delete[] readData;
    readData = nullptr;
}

