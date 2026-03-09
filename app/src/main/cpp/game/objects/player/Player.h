//
// Created by oto_9 on 06.03.2026.
//
#include <glm/glm.hpp>
#include "../GameObject.h"
#include "../base/GLObjectData.h"
#include "../primitives/Plane.h"
#include "../shaders/ShadersPaths.h"
#include "../base/Translation.h"
#include "PlayerRenderer.h"

class Player: public GameObject {
public:
    Translation translation = Translation(
            glm::vec3(0.0),glm::vec3(0.05), 0
    );
    glm::vec2 direction {};
    glm::vec2 velocity {};
    float speed = 0.07;

    PlayerRenderer renderer = PlayerRenderer([this]() { return translation.getModel(); });


    void init() override;
    void update() override;
    void destroy() override;
    void setRatio(float ratio) override;

    void onMove(float x, float y);
    void onUp();


private:


};
