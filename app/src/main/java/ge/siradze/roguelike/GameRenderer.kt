package ge.siradze.roguelike

import android.opengl.GLSurfaceView
import ge.siradze.roguelike.ui.UIEvent
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class GameRenderer: GLSurfaceView.Renderer {

    override fun onSurfaceCreated(gl: GL10, config: EGLConfig) {
        onSurfaceCreatedBridge()
    }

    override fun onDrawFrame(gl: GL10?) {
        onDrawFrameBridge()
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        onSurfaceChangedBridge(width, height)
    }

    fun onDestroy() {
        onDestroyBridge()
    }

    fun receiveEvent(event: UIEvent) {
        when (event) {
            is UIEvent.OnMove -> {
                onMove(event.move[0], event.move[1])
            }
            UIEvent.OnDown -> Unit
            UIEvent.OnUp -> {
                onUp()
            }
        }
    }

 /*

    external fun onTouchDownBridge(x: Int, y: Int)
    external fun onTouchBridge(x: Int, y: Int)
    external fun onTouchUpBridge(x: Int, y: Int)
*/


    private external fun onSurfaceCreatedBridge()

    private external fun onDrawFrameBridge()

    private external fun onSurfaceChangedBridge(width: Int, height: Int)

    private external fun onDestroyBridge()

    external fun onMove(x: Float, y: Float)
    external fun onUp()
}