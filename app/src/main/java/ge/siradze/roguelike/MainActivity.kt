package ge.siradze.roguelike

import android.content.res.AssetManager
import android.os.Bundle
import android.util.Log
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.viewinterop.AndroidView
import ge.siradze.roguelike.extentions.x
import ge.siradze.roguelike.extentions.y
import ge.siradze.roguelike.ui.GameUI
import ge.siradze.roguelike.ui.UIEvent

class MainActivity : ComponentActivity() {

    private lateinit var gameView : GameView


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        gameView = GameView(context = this)
        setAssetManager(assets)

        setContent {
            MaterialTheme {
                Surface(
                    modifier = Modifier.fillMaxSize(),
                    color = MaterialTheme.colorScheme.background
                ) {
                    ComposeGLSurfaceView()
                    GameUI { event ->
                        gameView.receiveEvent(event)
                        if(event is UIEvent.OnMove){
                            Log.i("MainActivity", "${event.move.x} ${event.move.y}")
                        }
                    }
                }
            }
        }
    }

    companion object {
        // Used to load the 'roguelike' library on application startup.
        init {
            System.loadLibrary("roguelike")
        }
        private external fun setAssetManager(assetManager: AssetManager)
    }

    @Composable
    fun ComposeGLSurfaceView() {
        AndroidView(factory = { gameView })
    }
}