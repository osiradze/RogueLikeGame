//
// Created by OSiradze on 13.07.25.
//

#define STB_IMAGE_IMPLEMENTATION
#include "OpenglUtils.h"
#include "../../assets/AssetManager.h"
#include "../../image/stb_image.h"
#include <GLES3/gl31.h>
#include <android/log.h>
#include <string>

bool OpenglUtils::createShader(int type, const char *code, unsigned int &shader) {
    shader = glCreateShader(type);
    glShaderSource(shader, 1, &code, nullptr);
    glCompileShader(shader);
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        __android_log_print(ANDROID_LOG_ERROR, "OpenglUtils", "%s", infoLog);
        return false;
    }
    return true;
}

bool OpenglUtils::createProgram(unsigned int vertexShader, unsigned int fragmentShader, unsigned int &program) {
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        __android_log_print(ANDROID_LOG_ERROR, "OpenglUtils", "%s", infoLog);
        return false;
    }
    return true;
}


bool OpenglUtils::createProgram(unsigned int &program, const char *vertexPath, const char *fragmentPath) {
    std::string vertexShaderSource = AssetManager::getFileStringContent(vertexPath);
    std::string fragmentShaderSource = AssetManager::getFileStringContent(fragmentPath);
    if(vertexShaderSource.empty() || fragmentShaderSource.empty()) {
        __android_log_print(ANDROID_LOG_ERROR, "OpenglUtils", "Failed to load shader source from files: %s, %s", vertexPath, fragmentPath);
        return false;
    }
    unsigned int vertexShader, fragmentShader;
    if(!OpenglUtils::createShader(GL_VERTEX_SHADER, vertexShaderSource.c_str(), vertexShader)) {
        return false;
    }
    if(!OpenglUtils::createShader(GL_FRAGMENT_SHADER, fragmentShaderSource.c_str(), fragmentShader)){
        return false;
    }
    auto success = OpenglUtils::createProgram(vertexShader, fragmentShader, program);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return success;
}

bool OpenglUtils::createComputeProgram(unsigned int &program, const char *computePath) {
    std::string computeShaderSource = AssetManager::getFileStringContent(computePath);
    if(computeShaderSource.empty()) {
        __android_log_print(ANDROID_LOG_ERROR, "OpenglUtils", "Failed to load compute shader source from file: %s", computePath);
        return false;
    }
    unsigned int computeShader;
    if(!OpenglUtils::createShader(GL_COMPUTE_SHADER, computeShaderSource.c_str(), computeShader)) {
        return false;
    }
    program = glCreateProgram();
    glAttachShader(program, computeShader);
    glLinkProgram(program);
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        __android_log_print(ANDROID_LOG_ERROR, "OpenglUtils", "%s", infoLog);
        return false;
    }
    glDeleteShader(computeShader);
    return true;
}

void OpenglUtils::loadTexture(const char *assetPath) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int w, h, ch;
    unsigned char* data = AssetManager::loadImageFromAssets(assetPath, w, h, ch);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    } else {
        __android_log_print(ANDROID_LOG_ERROR, "OpenglUtils", "Failed to load texture");
    }
}
