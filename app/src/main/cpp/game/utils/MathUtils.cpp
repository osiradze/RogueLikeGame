//
// Created by OSiradze on 24.07.25.
//
#include "MathUtils.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

glm::vec3 MathUtils::rotate(glm::vec3 vector, float degree, glm::vec3 axis) {
    glm::vec3 normalizedAxis = glm::normalize(axis);

    // Convert degrees to radians
    float radians = glm::radians(degree);

    // Use glm::rotate from rotate_vector.hpp to rotate the vector
    return glm::rotate(vector, radians, normalizedAxis);
}


bool MathUtils::areEqual(float a, float b, float epsilon) {
    return std::fabs(a - b) < epsilon;
}

bool MathUtils::match(glm::vec4 &array1, glm::vec4 &array2, int length, float epsilon) {
    for(int i = 0; i < length; i++) {
        if(!areEqual(array1[i], array2[i], epsilon)) {
            return false;
        }
    }
    return true;
}

float MathUtils::randomFloat(float min, float max) {
    float t = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    return min + t * (max - min);
}

