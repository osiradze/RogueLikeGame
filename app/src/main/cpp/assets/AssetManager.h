//
// Created by OSiradze on 13.07.25.
//

#pragma once
#include <string>
#include <android/asset_manager.h>


class AssetManager {
public:
    static AAssetManager* assetManager;
    static std::string getFileStringContent(const char* filePath);
    static unsigned char* loadImageFromAssets(const char* assetPath, int& width, int& height, int& channels);
};