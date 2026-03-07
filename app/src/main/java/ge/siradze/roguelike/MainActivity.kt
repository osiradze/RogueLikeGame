package ge.siradze.roguelike

import android.content.res.AssetManager
import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.viewinterop.AndroidView

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