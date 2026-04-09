//
// Created by oto_9 on 07.04.2026.
//

#pragma once
#include "GameObject.h"
#include "base/GLObjectData.h"
#include "shaders/ShadersPaths.h"
#include "base/UniformLocations.h"
#include <memory>

struct FortressProperties {
    int divisionX = 3;
    int divisionY = 4;
    int pointCount = 10000;
    float pointRadius = 0.01;
    // x, y, vx, vy, r, g, b, a
    int numberOfFloatsPerVertex = 8;
};

class Fortress: public GameObject{

public:
    void init() override;
    void update() override;
    void destroy() override;
    void setScreenWidth(int width) { screenWidth = width; }
    void setRatio(float r) override;

    explicit Fortress(
            std::function<glm::vec3()> getCameraPosition
    ) : getCameraPosition(std::move(getCameraPosition)){}

private:

    std::string name = "fortress";
    std::unique_ptr<GLObjectData> data;

    ShadersPaths shaders {
            "shaders/fortress/fortress_v.vert",
            "shaders/fortress/fortress_f.frag",
            "shaders/fortress/fortress_c.comp"
    };

    int screenWidth = 1;
    float ratio = 1.0;
    FortressProperties properties {};
    int imageWidth = 0;
    int imageHeight = 0;
    // flat RGBA floats [0.0, 1.0], size = imageWidth * imageHeight * 4
    std::unique_ptr<float[]> pixels;
    std::unique_ptr<float[]> fortressSprite;
    std::unique_ptr<float[]> fortressData;


    unsigned int shaderProgram {};
    unsigned int computeProgram {};

    unsigned int vao = 0;
    unsigned int vbo = 0;

    Uniforms renderUniforms;
    std::function<glm::vec3()> getCameraPosition;


    void importImage();
    std::unique_ptr<float[]> getSelectedRect(int x, int y);
    void generatePoints();


    void initRender();
    void initUniforms();
    void initData();
    void initRenderData();
    //void runCompute();
    void draw() const;


};

