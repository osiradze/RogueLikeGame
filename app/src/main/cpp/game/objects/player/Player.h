//
// Created by oto_9 on 06.03.2026.
//
#include <glm/glm.hpp>
#include "../GameObject.h"
#include "../base/GLObjectData.h"
#include "../primitives/Plane.h"
#include "../shaders/ShadersPaths.h"
#include "../base/Translation.h"
#include "renderer/PlayerRenderer.h"
#include "renderer/AimRenderer.h"
#include "../../../events/Move.h"

class Player: public GameObject {
public:
    Translation playerTranslation = Translation(
            glm::vec3(0.0), glm::vec3(0.06), 0
    );

    glm::vec3 direction{};
    glm::vec3 velocity{};
    float speed = 0.05;

    Translation aimTranslation = Translation(
            glm::vec3(0.0), glm::vec3(0.02), 0
    );
    glm::vec3 aimDirection{};
    float maxAimDistance = 0.4f;


    PlayerRenderer playerRenderer = PlayerRenderer(
            [this]() { return playerTranslation.getModel(); });
    AimRenderer aimRenderer = AimRenderer([this]() { return aimTranslation.getModel(); });


    void init() override;

    void update() override;

    void destroy() override;

    void setRatio(float ratio) override;

    void onMove(Move move);

    void onUp();


private:
    void clampAimPosition();
};
