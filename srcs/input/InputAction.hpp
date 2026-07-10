#pragma once

/* Abstract actions the game reacts to, independent of which physical
   key produced them. GameStates handle these; nothing upstream of
   KeyBindings ever needs to know a key code. */

enum class InputAction {
    MoveUp,
    MoveDown,
    MoveLeft,
    MoveRight,
    PlaceBomb,
    Quit,
};