//
// Created by oto_9 on 10.03.2026.
//
#pragma once
#include "base/GLObjectData.h"
#include "GameObject.h"
#include "shaders/ShadersPaths.h"
#include <glm/glm.hpp>

class Enemy: public GameObject {
public:
    void init() override;
    void update() override;
    void destroy() override;

    explicit Enemy(
            std::function<glm::vec3()> getPlayerPosition,
            std::function<glm::vec3()> getCameraPosition
    ) : getPlayerPosition(std::move(getPlayerPosition)), getCameraPosition(std::move(getCameraPosition)) {}
private:
    [[nodiscard]] std::unique_ptr<float[]> getData() const;

    int numberOfFloatsPerVertex = 4;
    int enemyCount = 100;


    std::unique_ptr<GLObjectData> data = std::make_unique<GLObjectData>(
            "enemy", numberOfFloatsPerVertex, enemyCount * numberOfFloatsPerVertex, getData()
    );

    ShadersPaths shaders {
            "shaders/enemy/enemy_v.vert",
            "shaders/enemy/enemy_f.frag",
            "shaders/enemy/enemy_c.comp"
    };

    std::function<glm::vec3()> getPlayerPosition;
    std::function<glm::vec3()> getCameraPosition;

    unsigned int shaderProgram {};
    unsigned int computeProgram {};
    unsigned int vao = 0;
    unsigned int vbo = 0;
    int u_camera = {};

    void initData();
    void runCompute() const;
    void draw() const;
};
