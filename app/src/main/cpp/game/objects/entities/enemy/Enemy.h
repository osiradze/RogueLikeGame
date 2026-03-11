//
// Created by oto_9 on 10.03.2026.
//
#pragma once
#include "base/GLObjectData.h"
#include "GameObject.h"
#include "shaders/ShadersPaths.h"

class Enemy: public GameObject {
public:
    void init() override;
    void update() override;
    void destroy() override;


private:
    [[nodiscard]] std::unique_ptr<float[]> getData() const;

    int numberOfFloatsPerVertex = 4;
    int enemyCount = 10;


    std::unique_ptr<GLObjectData> data = std::make_unique<GLObjectData>(
            "enemy", numberOfFloatsPerVertex, enemyCount * numberOfFloatsPerVertex, getData()
    );

    ShadersPaths shaders {
            "shaders/enemy/enemy_v.vert",
            "shaders/enemy/enemy_f.frag",
    };

    unsigned int shaderProgram {};
    unsigned int vao = 0;
    unsigned int vbo = 0;


    void initData();
    void draw() const;
};
