//
// Created by oto_9 on 06.03.2026.
//
#include <jni.h>
#include "game/GameRenderer.h"

std::unique_ptr<GameRenderer> gameRenderer;


extern "C"
JNIEXPORT void JNICALL
Java_ge_siradze_roguelike_GameRenderer_onSurfaceCreatedBridge(JNIEnv *env, jobject thiz) {
    gameRenderer = std::make_unique<GameRenderer>();
    gameRenderer->onSurfaceCreated();
}
extern "C"
JNIEXPORT void JNICALL
Java_ge_siradze_roguelike_GameRenderer_onDrawFrameBridge(JNIEnv *env, jobject thiz) {
    gameRenderer->onDrawFrame();
}
extern "C"
JNIEXPORT void JNICALL
Java_ge_siradze_roguelike_GameRenderer_onSurfaceChangedBridge(JNIEnv *env, jobject thiz, jint width,jint height) {
    gameRenderer->onSurfaceChanged(width, height);
}
extern "C"
JNIEXPORT void JNICALL
Java_ge_siradze_roguelike_GameRenderer_onDestroyBridge(JNIEnv *env, jobject thiz) {
    gameRenderer->onDestroy();
}