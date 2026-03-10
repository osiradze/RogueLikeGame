//
// Created by oto_9 on 09.03.2026.
//
#pragma once
#include "glm/glm.hpp"
#include "GameObject.h"
#include "base/GLObjectData.h"
#include "primitives/Plane.h"
#include "shaders/ShadersPaths.h"

class LineRenderer {
public:
    void init();
    void draw();
    void destroy();

    explicit LineRenderer(
            std::function<glm::vec3()> getPlayerPosition,
            std::function<glm::vec3()> getAimPosition
    ):getPlayerPosition(std::move(getPlayerPosition)), getAimPosition(std::move(getAimPosition)){}

private:
    std::unique_ptr<GLObjectData> data =  std::make_unique<GLObjectData>(
            "line",2,4,[](){
                return std::make_unique<float[]>(4);
            }()
    );
    ShadersPaths shaders {
            "shaders/player/line/line_v.vert",
            "shaders/player/line/line_f.frag",
    };

    std::function<glm::vec3()> getPlayerPosition;
    std::function<glm::vec3()> getAimPosition;

    unsigned int  shaderProgram {};
    unsigned int vao = 0;
    unsigned int vbo = 0;

    void initUniforms();
    void initData();
    void updateData();

};
