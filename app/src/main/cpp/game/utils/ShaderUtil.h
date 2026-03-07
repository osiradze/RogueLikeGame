//
// Created by OSiradze on 28.08.25.
//

#pragma once

#include <functional>
#include <vector>


class ShaderUtil {
public:
    static void computeShader(
            unsigned int shaderProgram,
            const std::function<void()>& uniforms = []{},
            unsigned int* vbos = nullptr,
            unsigned int vboCount = 0,
            int x = 1, int y = 1, int z = 1
    );
};
