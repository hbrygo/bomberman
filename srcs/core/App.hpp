#pragma once

#include <memory>
#include "GameState.hpp"

/* Owns exactly one active GameState and forwards input/update/render
   to it. States request transitions through App rather than reaching
   into each other directly -- e.g. a PlayingState would call
   app.changeState(std::make_unique<PausedState>(...)) in response to
   a Quit/Pause action, instead of holding a reference to PausedState
   itself. */

class App {
    public:
        void changeState(std::unique_ptr<GameState> next) {
            if (_current)
                _current->onExit();
            _current = std::move(next);
            _current->onEnter();
        }

        void handleAction(InputAction action) { if (_current) _current->handleAction(action); }
        void update(float dt)                 { if (_current) _current->update(dt); }
        void render()                         { if (_current) _current->render(); }

    private:
        std::unique_ptr<GameState> _current;
};