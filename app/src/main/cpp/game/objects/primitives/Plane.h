//
// Created by OSiradze on 02.08.25.
//
#pragma once

#include "../base/GLObjectData.h"

class Plane {
private:
    int floatsPerVertex = 2;
    int dataCount = 8;
    float* vertexData = new float[dataCount] {
            -0.5f, -0.5f, // bottom-left
             0.5f, -0.5f, // bottom-right
             0.5f,  0.5f, // top-right
            -0.5f,  0.5f  // top-left
    };

    int indicesDataCount = 6;
    unsigned int* indices = new unsigned int[indicesDataCount] {
            0, 2, 1,    // Counter-clockwise: bottom-left → top-right → bottom-right
            0, 3, 2     // Counter-clockwise: bottom-left → top-left → top-right
    };

public:
    std::unique_ptr<GLObjectData> getData() {
        return std::make_unique<GLObjectData>(
                "Plane",
                Plane::floatsPerVertex,
                Plane::dataCount,
                std::unique_ptr<float[]>(vertexData),
                Plane::indicesDataCount,
                std::unique_ptr<unsigned int[]>(indices)
        );
    }

};
