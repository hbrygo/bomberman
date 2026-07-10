#include "KeyBindings.hpp"
#include <GLFW/glfw3.h>

KeyBindings::KeyBindings() {
    bind(GLFW_KEY_W,      InputAction::MoveUp);
    bind(GLFW_KEY_S,      InputAction::MoveDown);
    bind(GLFW_KEY_A,      InputAction::MoveLeft);
    bind(GLFW_KEY_D,      InputAction::MoveRight);
    // bind(GLFW_KEY_SPACE,  InputAction::PlaceBomb);
    bind(GLFW_KEY_I,      InputAction::MoveUpP2);
    bind(GLFW_KEY_K,      InputAction::MoveDownP2);
    bind(GLFW_KEY_J,      InputAction::MoveLeftP2);
    bind(GLFW_KEY_L,      InputAction::MoveRightP2);
    // bind(GLFW_KEY_SPACE,  InputAction::PlaceBombP2);
    bind(GLFW_KEY_ESCAPE, InputAction::Quit);
}

bool KeyBindings::resolve(int key, InputAction& out) const {
    auto it = _map.find(key);
    if (it == _map.end())
        return false;
    out = it->second;
    return true;
}