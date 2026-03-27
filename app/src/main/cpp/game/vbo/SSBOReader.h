//
// Created by oto_9 on 18.03.2026.
//

#include <string>
#include <unordered_map>
#include <vector>

#pragma once

#include "ISSBOBuffer.h"

class SSBOReader : public ISSBOBuffer {
public:
    SSBOReader();
    void allocate(const std::string& key, int length) override;
    void init();
    void read();
    void destroy();
    std::vector<float> getData(const std::string& key) override;
    [[nodiscard]] unsigned int getSSBO() const override { return ssbo; }
private:
    std::unordered_map<std::string, std::pair<unsigned int, unsigned int>> buffers;
    float* cleanData = nullptr;
    float* readData  = nullptr;
    unsigned int size = 0;

    unsigned int ssbo;
};