#pragma once

#include "core/GameState.hpp"
#include "render/Shader.hpp"
#include "render/QuadMesh.hpp"
#include "entities/Player.hpp"
#include "window/Window.hpp"

/* The actual Bomberman gameplay screen: owns the shader and the
   player, and turns InputActions into gameplay effects. Menu/pause
   concerns belong in sibling GameStates, not here -- keep this one
   focused on "the game is being played". */

class PlayingState : public GameState {
    public:
        PlayingState(Window& window, const QuadMesh& mesh, int gridCols, int gridRows);

        void handleAction(InputAction action) override;
        void update(float dt) override;
        void render() override;

    private:
        Window& _window;
        Shader  _shader;
        Player  _player;
};