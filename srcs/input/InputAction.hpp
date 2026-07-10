#pragma once

/* Abstract actions the game reacts to, independent of which physical
   key produced them. GameStates handle these; nothing upstream of
   KeyBindings ever needs to know a key code. */

enum class InputAction {
    MoveUp,
    MoveDown,
    MoveLeft,
    MoveRight,
    MoveUpP2,
    MoveDownP2,
    MoveLeftP2,
    MoveRightP2,
    PlaceBomb,
    PlaceBombP2,
    Quit,
};