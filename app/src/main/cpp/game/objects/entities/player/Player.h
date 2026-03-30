//
// Created by oto_9 on 06.03.2026.
//
#pragma once
#include <glm/glm.hpp>
#include "GameObject.h"
#include "base/GLObjectData.h"
#include "primitives/Plane.h"
#include "shaders/ShadersPaths.h"
#include "base/Translation.h"
#include "renderer/PlayerRenderer.h"
#include "renderer/aim/AimRenderer.h"
#include "renderer/line/LineRenderer.h"
#include "events/Move.h"
#include "time/DeltaTime.h"
#include "entities/IEnemyTarget.h"

struct PlayerProperties {
    float speed = 0.05;
    float playerSize = 0.03;
    float aimDistance = 0.3;
    float aimSize = 0.02;
};

class Player: public GameObject, public IEnemyTarget {
public:

    void init() override;

    void update() override;

    void destroy() override;

    void setRatio(float ratio) override;

    void onMove(Move move);

    void onUp();

    [[nodiscard]] glm::vec3 getPosition() const override;
    void inCollision() override;

    std::function<glm::vec3()> getPositionFunction() {
        return [this]() { return getPosition(); };
    }

    explicit Player(std::function<glm::vec3()> getCameraPosition) : getCameraPosition(std::move(getCameraPosition)) {}


private:
    PlayerProperties properties {};
    Translation playerTranslation = Translation(
            glm::vec3(0.0), glm::vec3(properties.playerSize), 0
    );

    Translation aimTranslation = Translation(
            glm::vec3(0.0), glm::vec3(properties.aimSize), 0
    );
    glm::vec3 aimDirection{};

    std::function<glm::vec3()> getCameraPosition;

    PlayerRenderer playerRenderer = PlayerRenderer(
            [this]() { return playerTranslation.getModel(); },
            getCameraPosition);
    AimRenderer aimRenderer = AimRenderer(
            [this]() { return aimTranslation.getModel(); },
            getCameraPosition);
    LineRenderer lineRenderer = LineRenderer(
            [this]() { return playerTranslation.getPosition(); },
            [this]() { return aimTranslation.getPosition(); },
            getCameraPosition);

    glm::vec3 direction{};
    glm::vec3 velocity{};

};
