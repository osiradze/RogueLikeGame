//
// Created by oto_9 on 06.03.2026.
//


#include <GLES3/gl31.h>
#include "GameRenderer.h"


void GameRenderer::initGLConfig() {

}
void GameRenderer::clearBuffers() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glStencilMask(0xFF);        // enable writing to the stencil buffer

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glStencilMask(0x00);
}

