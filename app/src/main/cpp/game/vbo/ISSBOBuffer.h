//
// Created by oto_9 on 27.03.2026.
//
#pragma once

#include <string>
#include <vector>

class ISSBOBuffer {
public:
    virtual void allocate(const std::string& key, int length) = 0;
    virtual std::vector<float> getData(const std::string& key) = 0;
    virtual unsigned int getSSBO() const = 0;
    virtual ~ISSBOBuffer() = default;
};

