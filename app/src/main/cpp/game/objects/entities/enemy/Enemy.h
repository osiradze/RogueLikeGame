//
// Created by oto_9 on 10.03.2026.
//
#pragma once
#include "base/GLObjectData.h"
#include "base/UniformLocations.h"
#include "GameObject.h"
#include "shaders/ShadersPaths.h"
#include "vbo/ISSBOBuffer.h"
 #include "entities/IEnemyTarget.h"
#include "game/objects/entities/bullets/api/BulletsApi.h"
#include "entities/bullets/api/BulletUniforms.h"
#include "EnemyUniforms.h"
#include <glm/glm.hpp>

struct EnemyProperties {
    // position 2 - x,y, velocity 2 - vx vy, chasing - 1, in area
    // x, y, vx, vy, stopper, i, r, g, b
    int numberOfFloatsPerVertex = 9;
    int enemyCount = 2000;
    float radius = 0.02f;
    float size = 2.0;
    float detectionRadius = 1.5f;
    float enemySpeed = 0.1f;
};

class Enemy: public GameObject {
public:
    void init() override;
    void update() override;
    void destroy() override;
    void setScreenWidth(int width) { screenWidth = width; }
    void setBulletsApi(BulletsApi api) { bulletsApi = api; }

    explicit Enemy(
            IEnemyTarget* target,
            std::function<glm::vec3()> getCameraPosition,
            ISSBOBuffer* reader
    ) :
    target(target),
    getCameraPosition(std::move(getCameraPosition)),
    reader(reader) {}
private:
    std::string name = "enemy";
    EnemyProperties properties {};
    glm::vec4 spawnBounds = glm::vec4(-properties.size, -properties.size, properties.size, properties.size);

    [[nodiscard]] std::unique_ptr<float[]> getData() const;
    std::unique_ptr<GLObjectData> data = std::make_unique<GLObjectData>(
            name,
            properties.numberOfFloatsPerVertex,
            properties.enemyCount * properties.numberOfFloatsPerVertex,
            getData()
    );

    ShadersPaths shaders {
            "shaders/enemy/enemy_v.vert",
            "shaders/enemy/enemy_f.frag",
            "shaders/enemy/enemy_c.comp"
    };
    int screenWidth = 1;

    IEnemyTarget* target;
    std::function<glm::vec3()> getCameraPosition;

    unsigned int shaderProgram {};
    unsigned int computeProgram {};
    unsigned int vao = 0;
    unsigned int vbo = 0;

    BulletsApi bulletsApi {};

    Uniforms renderUniforms;
    Uniforms computeUniforms;
    EnemyUniforms enemyUniform {};
    BulletUniforms bulletsUniforms {};


    ISSBOBuffer* reader;
    unsigned int ssboOffset = 0;
    int readSize = 4;



    void initRender();
    void initUniforms();
    void initData();
    void runCompute();
    void draw() const;
    void handleReadData(std::vector<float> data);
};

