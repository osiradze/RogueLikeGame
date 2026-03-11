//
// Created by oto_9 on 12.03.2026.
//
#include "Camera.h"
#include "time/DeltaTime.h"
#include <cmath>
#include <glm/glm.hpp>

void Camera::update() {
    float t = 1.0f - std::exp(-smoothSpeed * DeltaTime::deltaTime);
    glm::vec3 target = getPlayerPosition();
    position = position + (target - position) * t;
}

void Camera::setPlayerPositionFunction(std::function<glm::vec3()> getPlayerPosition){
    this->getPlayerPosition = std::move(getPlayerPosition);
}

glm::vec3 Camera::getPosition() {
    return position;
}


