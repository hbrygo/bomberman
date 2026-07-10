#pragma once

#include "input/InputAction.hpp"

/* Base interface for any distinct "screen" of the game (main menu,
   playing, paused, settings, game over...). App owns exactly one
   active GameState at a time and forwards input/update/render to it.

   onEnter/onExit exist for setup/teardown that shouldn't live in the
   constructor/destructor -- e.g. starting menu music on enter,
   stopping it on exit, without destroying the object itself. */

class GameState {
    public:
        virtual ~GameState() = default;

        virtual void onEnter() {}
        virtual void onExit()  {}

        virtual void handleAction(InputAction action) = 0;
        virtual void update(float dt) = 0;
        virtual void render() = 0;
};