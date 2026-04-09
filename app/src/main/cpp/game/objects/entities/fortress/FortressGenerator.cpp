//
// Created by oto_9 on 08.04.2026.
//
#include "Fortress.h"
#include "assets/AssetManager.h"
#include "image/stb_image.h"
#include <android/log.h>
#include <random>

void Fortress::importImage() {
    int channels = 0;
    unsigned char* data = AssetManager::loadImageFromAssets(
        "images/fortress.png", imageWidth, imageHeight, channels
    );

    if (!data) {
        __android_log_print(ANDROID_LOG_ERROR, "Fortress", "Failed to load fortress.png");
        return;
    }

    const int count = imageWidth * imageHeight;
    pixels = std::make_unique<float[]>(count * 4);
    for (int i = 0; i < count; i++) {
        pixels[i * 4 + 0] = data[i * 4 + 0] / 255.0f; // r
        pixels[i * 4 + 1] = data[i * 4 + 1] / 255.0f; // g
        pixels[i * 4 + 2] = data[i * 4 + 2] / 255.0f; // b
        pixels[i * 4 + 3] = data[i * 4 + 3] / 255.0f; // a
    }

    stbi_image_free(data);

    __android_log_print(ANDROID_LOG_DEBUG, "Fortress",
        "Loaded fortress.png: %dx%d, %d pixels", imageWidth, imageHeight, count);
}

std::unique_ptr<float[]> Fortress::getSelectedRect(int x, int y) {
    const int rectWidth = imageWidth / properties.divisionX;
    const int rectHeight = imageHeight / properties.divisionY;

    auto rectPixels = std::make_unique<float[]>(rectWidth * rectHeight * 4);
    for (int j = 0; j < rectHeight; j++) {
        for (int i = 0; i < rectWidth; i++) {
            int srcIndex = ((y * rectHeight + j) * imageWidth + (x * rectWidth + i)) * 4;
            int dstIndex = (j * rectWidth + i) * 4;
            rectPixels[dstIndex + 0] = pixels[srcIndex + 0];
            rectPixels[dstIndex + 1] = pixels[srcIndex + 1];
            rectPixels[dstIndex + 2] = pixels[srcIndex + 2];
            rectPixels[dstIndex + 3] = pixels[srcIndex + 3];
        }
    }
    return rectPixels;
};

void Fortress::generatePoints() {
    if (!fortressSprite) return;

    const int rectWidth  = imageWidth  / properties.divisionX;
    const int rectHeight = imageHeight / properties.divisionY;

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> distX(0, rectWidth  - 1);
    std::uniform_int_distribution<int> distY(0, rectHeight - 1);

    fortressData = std::make_unique<float[]>(properties.pointCount * properties.numberOfFloatsPerVertex);

    for (int i = 0; i < properties.pointCount; i++) {
        const int px = distX(rng);
        const int py = distY(rng);

        const int pixelIndex = (py * rectWidth + px) * 4;
        const float r = fortressSprite[pixelIndex + 0];
        const float g = fortressSprite[pixelIndex + 1];
        const float b = fortressSprite[pixelIndex + 2];
        float a = fortressSprite[pixelIndex + 3];

        // Map pixel (px, py) to normalised world coords [-0.5, 0.5]
        const float x = static_cast<float>(px) / static_cast<float>(rectWidth)  - 0.5f;
        const float y = static_cast<float>(py) / static_cast<float>(rectHeight) - 0.5f;

        float white = 0.8;
        if(r > white && g > white && b > white) {
            continue;
        }


        const int offset = i * properties.numberOfFloatsPerVertex;
        fortressData[offset + 0] = x;
        fortressData[offset + 1] = y;
        fortressData[offset + 2] = 0.0f; // vx
        fortressData[offset + 3] = 0.0f; // vy
        fortressData[offset + 4] = r;
        fortressData[offset + 5] = g;
        fortressData[offset + 6] = b;
        fortressData[offset + 7] = a;
    }
}

void Fortress::initData() {
    data = std::make_unique<GLObjectData>(
            name,
            properties.numberOfFloatsPerVertex,
            properties.pointCount * properties.numberOfFloatsPerVertex,
            std::move(fortressData)
    );
}

