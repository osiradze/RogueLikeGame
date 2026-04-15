//
// Created by oto_9 on 09.03.2026.
//
#pragma once
#include "glm/glm.hpp"
#include "GameObject.h"
#include "base/GLObjectData.h"
#include "primitives/Plane.h"
#include "shaders/ShadersPaths.h"
#include "base/UniformLocations.h"

class AimRenderer {
public:
    void init();
    void draw();
    void destroy();
    void setRatio(float r);

    explicit AimRenderer(std::function<glm::mat4()> getModel, std::function<glm::vec3()> getCameraPosition)
        : getModel(std::move(getModel)), getCameraPosition(std::move(getCameraPosition)) {}

private:
    std::unique_ptr<GLObjectData> data = Plane().getData();
    ShadersPaths shaders {
            "shaders/player/aim/aim_v.vert",
            "shaders/player/aim/aim_f.frag",
    };

    std::function<glm::mat4()> getModel;
    std::function<glm::vec3()> getCameraPosition;
    float ratio = 1.0f;

    unsigned int  shaderProgram {};
    unsigned int vao = 0;
    unsigned int vbo = 0;
    unsigned int ebo = 0;

    Uniforms uniforms;

    void initUniforms();
    void initData();
    void updateData();
};
