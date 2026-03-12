package ge.siradze.roguelike

import android.content.res.AssetManager
import android.os.Bundle
import android.util.Log
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.mutableIntStateOf
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.Color.Companion
import androidx.compose.ui.unit.dp
import androidx.compose.ui.viewinterop.AndroidView
import ge.siradze.roguelike.extentions.x
import ge.siradze.roguelike.extentions.y
import ge.siradze.roguelike.ui.GameUI
import ge.siradze.roguelike.ui.UIEvent
import kotlinx.coroutines.delay
import kotlin.coroutines.coroutineContext

class MainActivity : ComponentActivity() {

    private lateinit var gameView : GameView


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        gameView = GameView(context = this)
        setAssetManager(assets)



        setContent {
            val fps = remember { mutableIntStateOf(0) }
            LaunchedEffect(Unit) {
                while (true) {
                    delay(2000)
                    fps.intValue = getFPS()
                }
            }


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
                    FpsView(fps.intValue)
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

external fun getFPS(): Int

@Composable
fun FpsView(fps: Int) {
    Text(
        text = "FPS: $fps",
        color = Color.White,
        modifier = Modifier.padding(40.dp)
    )
}