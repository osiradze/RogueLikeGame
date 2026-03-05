//
// Created by oto_9 on 06.03.2026.
//
#include <glm/glm.hpp>
#include "../GameObject.h"

class Player: public GameObject {
public:
    glm::vec2 position {};
    glm::vec2 velocity {};
    glm::vec2 acceleration {};

    void init() override;
    void onDraw() override;
    void destroy() override;
};
