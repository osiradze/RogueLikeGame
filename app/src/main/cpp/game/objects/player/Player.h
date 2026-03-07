//
// Created by oto_9 on 06.03.2026.
//
#include <glm/glm.hpp>
#include "../GameObject.h"
#include "../base/GLObjectData.h"
#include "../primitives/Plane.h"
#include "../shaders/ShadersPaths.h"

class Player: public GameObject {
public:
    glm::vec2 position {};
    glm::vec2 velocity {};
    glm::vec2 acceleration {};

    std::unique_ptr<GLObjectData> data = Plane().getData();
    ShadersPaths shaders {
            "shaders/vertex.glsl",
            "shaders/fragment.glsl",
    };
    unsigned int  shaderProgram;

    void init() override;
    void onDraw() override;
    void destroy() override;

private:
    void initUniforms();
    void initData();
    void initTexture();

};
