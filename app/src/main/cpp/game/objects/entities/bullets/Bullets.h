//
// Created by oto_9 on 30.03.2026.
//

#include "GameObject.h"
#include "base/GLObjectData.h"
#include "shaders/ShadersPaths.h"
#include "base/UniformLocations.h"

struct BulletProperties {
    int numberOfFloatsPerVertex = 7;
    int maxBullets = 50;
    float bulletRadius = 0.02f;
    float impactRadius = 0.1;
};

class Bullets: public GameObject {
public:
    void init() override;

    void update() override;

    void destroy() override;
    explicit Bullets(
            std::function<glm::vec3()> getCameraPosition
    ) : getCameraPosition(std::move(getCameraPosition)){}

private:
    BulletProperties properties {};

    std::string name = "bullets";
    [[nodiscard]] std::unique_ptr<float[]> getData() const;
    std::unique_ptr<GLObjectData> data = std::make_unique<GLObjectData>(
            name,
            properties.numberOfFloatsPerVertex,
            properties.maxBullets * properties.numberOfFloatsPerVertex,
            getData()
    );

    ShadersPaths shaders {
            "shaders/bullets/enemy_v.vert",
            "shaders/bullets/enemy_f.frag",
            "shaders/bullets/enemy_c.comp"
    };

    unsigned int shaderProgram {};
    unsigned int computeProgram {};
    unsigned int vao = 0;
    unsigned int vbo = 0;

    Uniforms renderUniforms;
    Uniforms computeUniforms;

    std::function<glm::vec3()> getCameraPosition;


    void initRender();
    void initUniforms();
    void initData();
    void runCompute();
    void draw() const;



};
