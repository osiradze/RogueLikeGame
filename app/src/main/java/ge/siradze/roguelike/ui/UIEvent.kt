package ge.siradze.roguelike.ui

sealed class UIEvent {
    data object OnDown: UIEvent()
    data object OnUp: UIEvent()
    class OnMove(val move: FloatArray, val cNumber: Int): UIEvent()
}