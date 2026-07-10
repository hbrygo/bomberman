#pragma once

#include <unordered_map>
#include "InputAction.hpp"

/* Maps a physical GLFW key code -> abstract InputAction. Constructed
   with sensible defaults (WASD + Space + Escape) but rebindable at
   runtime, e.g. from a settings menu. Deliberately has no notion of
   *saving* bindings yet -- that's a serialization concern to add
   once the settings/save system exists. */

class KeyBindings {
    public:
        KeyBindings(); // populates defaults

        void bind(int key, InputAction action) { _map[key] = action; }
        void unbind(int key)                   { _map.erase(key); }

        // Returns true and fills `out` if `key` is currently bound.
        bool resolve(int key, InputAction& out) const;

    private:
        std::unordered_map<int, InputAction> _map;
};