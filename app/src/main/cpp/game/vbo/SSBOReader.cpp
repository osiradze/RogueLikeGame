//
// Created by oto_9 on 18.03.2026.
//
#include <GLES3/gl31.h>
#include "SSBOReader.h"

SSBOReader::SSBOReader() {
    glGenBuffers(1, &ssbo);
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
    delete[] readData;
    readData = (float*)glMapBufferRange(
            GL_SHADER_STORAGE_BUFFER, 0,
            size * sizeof(float),
            GL_MAP_READ_BIT
    );
    init();
}

void SSBOReader::allocate(const std::string& key, int length) {
    buffers[key] = std::make_pair(size, length);
    size += length;
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

