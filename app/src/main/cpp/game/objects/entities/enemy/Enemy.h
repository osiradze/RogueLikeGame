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
    void setScreenWidth(int width) { screenWidth = width; }

    explicit Enemy(
            std::function<glm::vec3()> getPlayerPosition,
            std::function<glm::vec3()> getCameraPosition
    ) : getPlayerPosition(std::move(getPlayerPosition)), getCameraPosition(std::move(getCameraPosition)) {}
private:
    [[nodiscard]] std::unique_ptr<float[]> getData() const;

    int numberOfFloatsPerVertex = 5;
    int enemyCount = 1000;
    float radius = 0.02f;
    int screenWidth = 1;

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
    int u_point_size = {};

    void initData();
    void runCompute() const;
    void draw() const;
};
