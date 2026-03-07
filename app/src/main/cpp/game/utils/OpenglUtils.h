//
// Created by OSiradze on 13.07.25.
//

#pragma once
#include <string>

class OpenglUtils {
public:
    static bool createShader(int type, const char *code, unsigned int &shader);
    static bool createProgram(unsigned int vertexShader, unsigned int fragmentShader, unsigned int &program);
    static bool createProgram(unsigned int &program, const char *vertexPath, const char *fragmentPath);
    static void loadTexture(const char* assetPath);

    static bool createComputeProgram(unsigned int &program, const char *computePath);
};