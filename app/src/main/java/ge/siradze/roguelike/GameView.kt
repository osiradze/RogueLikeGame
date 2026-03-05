package ge.siradze.roguelike

import android.content.Context
import android.opengl.GLSurfaceView

class GameView(context: Context) : GLSurfaceView(context) {

    private val gameRenderer: GameRenderer = GameRenderer()

    init {
        setEGLContextClientVersion(3)
        setRenderer(gameRenderer) // Set the renderer for this view
        renderMode = RENDERMODE_CONTINUOUSLY // Render continuously
    }

    override fun onDetachedFromWindow() {
        super.onDetachedFromWindow()
        gameRenderer.onDestroy()
    }

}