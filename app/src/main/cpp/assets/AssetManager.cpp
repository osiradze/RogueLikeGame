//
// Created by OSiradze on 13.07.25.
//

#include "AssetManager.h"
#include "../image/stb_image.h"
#include <android/asset_manager.h>
#include <android/log.h>

AAssetManager* AssetManager::assetManager = nullptr;

std::string AssetManager::getFileStringContent(const char *filePath) {
    if (!assetManager) {
        __android_log_print(ANDROID_LOG_ERROR, "ShaderLoader", "AssetManager is null!");
        return "";
    }

    AAsset* file = AAssetManager_open(assetManager, filePath, AASSET_MODE_BUFFER);
    if (!file) {
        __android_log_print(ANDROID_LOG_ERROR, "OpenglUtils", "Failed to open: %s", filePath);
        return "";
    }

    size_t size = AAsset_getLength(file);
    std::string content(size, '\0');
    AAsset_read(file, content.data(), size);
    AAsset_close(file);
    return content;
}


unsigned char* AssetManager::loadImageFromAssets(const char* assetPath, int& width, int& height, int& channels) {
    if (!assetManager) {
        __android_log_print(ANDROID_LOG_ERROR, "ImageLoader", "AssetManager not set");
        return nullptr;
    }

    AAsset* asset = AAssetManager_open(assetManager, assetPath, AASSET_MODE_BUFFER);
    if (!asset) {
        __android_log_print(ANDROID_LOG_ERROR, "ImageLoader", "Failed to open asset: %s", assetPath);
        return nullptr;
    }

    off_t length = AAsset_getLength(asset);
    auto* buffer = new unsigned char[length];
    AAsset_read(asset, buffer, length);
    AAsset_close(asset);

    stbi_set_flip_vertically_on_load(true);
    unsigned char* image = stbi_load_from_memory(buffer, length, &width, &height, &channels, 4);
    delete[] buffer;

    if (!image) {
        __android_log_print(ANDROID_LOG_ERROR, "ImageLoader", "stb_image failed: %s", stbi_failure_reason());
    }

    return image;
}