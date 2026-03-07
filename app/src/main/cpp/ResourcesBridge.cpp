#include <jni.h>
#include "assets/AssetManager.h"

//
// Created by OSiradze on 13.07.25.
//
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

extern "C"
JNIEXPORT void JNICALL
Java_ge_siradze_roguelike_MainActivity_00024Companion_setAssetManager(JNIEnv *env, jobject thiz,
                                                                      jobject asset_manager) {
    AssetManager::assetManager = AAssetManager_fromJava(env, asset_manager);
}