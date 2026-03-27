//
// Created by OSiradze on 03.08.25.
//

#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

struct Translation {

private:
    float ratio = 1.0f;
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
    glm::mat4 model = glm::mat4(1.0f);

    bool isDirty = true;

public:
    explicit Translation(
        glm::vec3 position = glm::vec3(0.0f),
        glm::vec3 scale = glm::vec3(1.0f),
        float rotation = 0
    ) : position(position), scale(scale), rotation(glm::vec3(0, 0, rotation)) {}

    void move(const glm::vec2 p) {
        this->position += glm::vec3(p.x * ratio, p.y, 0.0);
        isDirty = true;
    }
    void setPosition(const glm::vec3 p) {
        this->position = p;
        isDirty = true;
    }

    glm::vec3 getPosition() const {
        return this->position;
    }

    void setScale(const glm::vec3 s) {
        this->scale = s;
        isDirty = true;
    }

    void scaleUp(const glm::vec3 s) {
        this->scale *= s;
        isDirty = true;
    }

    [[nodiscard]] glm::vec3 getScale() const {
        return this->scale;
    }

    void setRotation(const float r) {
        this->rotation = glm::vec3(0,0,r);
        isDirty = true;
    }

    void rotate(const float r) {
        this->rotation.z += r;
        isDirty = true;
    }

    glm::mat4 getModel() {
        if(isDirty) {
            updateModelMatrix();
        }
        return model;
    }

    void setRatio(float r) {
        ratio = r;
        isDirty = true;
    }

    [[nodiscard]] float getRatio() const {
        return ratio;
    }

private:
    void updateModelMatrix() {
        glm::quat q = glm::quat(glm::radians(rotation));
        glm::mat4 rot = glm::toMat4(q);

        model = glm::translate(glm::mat4(1.0f), position);
        model *= glm::scale(glm::mat4(1.0f), glm::vec3(ratio, 1.0f, 1.0f));
        model *= rot;
        model *= glm::scale(glm::mat4(1.0f), scale);
        isDirty = false;
    }
};