//
// Created by oto_9 on 06.03.2026.
//

#include "objects/player/Player.h"

class GameRenderer {
public:

    void onSurfaceCreated();

    void onDrawFrame();

    void onSurfaceChanged(int width, int height);

    void onDestroy();

    void onMove(float x, float y);
    void onUp();

private:

    std::unique_ptr<Player> player;




    static void initGLConfig();
    static void clearBuffers();
};
