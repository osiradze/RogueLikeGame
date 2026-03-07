//
// Created by OSiradze on 24.07.25.
//
#pragma once
#include <glm/glm.hpp>

class MathUtils {
public:
    static glm::vec3 rotate(glm::vec3 vector, float degree, glm::vec3 axis);
    static bool areEqual(float a, float b, float epsilon);
    static bool match(glm::vec4 &array1, glm::vec4 &array2, int length, float epsilon);
    static float randomFloat(float min = 0.0, float max = 1.0);
};
