//
// Created by oto_9 on 27.03.2026.
//
#pragma once
#include <glm/glm.hpp>

class IEnemyTarget {
public:
    [[nodiscard]] virtual glm::vec3 getPosition() const = 0;
    virtual void inCollision() {};
    virtual ~IEnemyTarget() = default;
};
