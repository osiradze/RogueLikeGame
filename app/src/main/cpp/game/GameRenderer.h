//
// Created by oto_9 on 06.03.2026.
//

#include "objects/entities/player/Player.h"
#include "entities/enemy/Enemy.h"

class GameRenderer {
public:

    void onSurfaceCreated();

    void onDrawFrame();

    void onSurfaceChanged(int width, int height);

    void onDestroy();

    void onMove(Move move);
    void onUp();

private:

    std::unique_ptr<Player> player;
    std::unique_ptr<Enemy> enemy;




    static void initGLConfig();
    static void clearBuffers();
};
