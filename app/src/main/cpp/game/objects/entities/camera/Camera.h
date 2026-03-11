//
// Created by oto_9 on 12.03.2026.
//

#include "glm/vec3.hpp"

class Camera {
public:
    void setPlayerPositionFunction(std::function<glm::vec3()> getPlayerPosition);
    void update();
    glm::vec3 getPosition();

    std::function<glm::vec3()> getPositionFunction() {
        return [this]() { return getPosition(); };
    }

private:
    std::function<glm::vec3()> getPlayerPosition;
    glm::vec3 position {0 ,0, 0};

    float smoothSpeed = 5.0f;



};
