//
// Created by oto_9 on 08.03.2026.
//

#pragma once

#include <functional>
#include "../primitives/Plane.h"
#include "../shaders/ShadersPaths.h"
#include "../base/Translation.h"

class PlayerRenderer {
public:
    void init();
    void draw();
    void destroy();

    explicit PlayerRenderer(std::function<glm::mat4()> getModel): getModel(std::move(getModel)) {}
private:
    std::unique_ptr<GLObjectData> data = Plane().getData();
    ShadersPaths shaders {
            "shaders/player/player_v.vert",
            "shaders/player/player_f.frag",
    };

    std::function<glm::mat4()> getModel;


    unsigned int  shaderProgram {};
    unsigned int vao = 0;
    unsigned int vbo = 0;
    unsigned int ebo = 0;

    int u_model = {};

    void initUniforms();
    void initData();
    void initTexture();
    void updateUniforms();
};
