//
// Created by oto_9 on 30.03.2026.
//

#include "GameObject.h"
#include "base/GLObjectData.h"
#include "shaders/ShadersPaths.h"
#include "base/UniformLocations.h"
#include "game/objects/entities/bullets/api/BulletsApi.h"
#include "entities/bullets/api/BulletUniforms.h"

struct BulletProperties {
    // vertex attributes: position (x, y), velocity (x, y), color (r, g, b), isAlive, lifetime
    int numberOfFloatsPerVertex = 9;
    int maxBullets = 50;
    float bulletRadius = 0.05f;
    float impactRadius = 0.1f;
    float bulletSpeed = 1.5f;
};

class Bullets: public GameObject {
public:
    void init() override;

    void update() override;

    void spawn(glm::vec2 position, glm::vec2 direction);

    void setScreenWidth(int width) { screenWidth = width; }
    void setRatio(float r) override;

    BulletsApi getApi() {
        return BulletsApi {
            vbo,
            properties.numberOfFloatsPerVertex,
            properties.maxBullets,
            properties.impactRadius
        };
    }

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
            "shaders/bullets/bullets_v.vert",
            "shaders/bullets/bullets_f.frag",
            "shaders/bullets/bullets_c.comp"
    };
    std::string spawnShaderPath = "shaders/bullets/bullets_spawn.comp";
    int screenWidth = 1;
    float ratio = 1.0f;

    unsigned int shaderProgram {};
    unsigned int computeProgram {};
    unsigned int spawnProgram {};
    unsigned int vao = 0;
    unsigned int vbo = 0;

    Uniforms renderUniforms;
    Uniforms computeUniforms;
    BulletUniforms bulletUniforms;

    std::function<glm::vec3()> getCameraPosition;


    void initRender();
    void initUniforms();
    void initData();
    void runCompute();
    void draw() const;



};
