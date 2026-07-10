#pragma once

#include <vector>
#include "core/GameState.hpp"
#include "render/Shader.hpp"
#include "render/QuadMesh.hpp"
#include "entities/Player.hpp"
#include "entities/Bomb.hpp"
#include "window/Window.hpp"

/* The actual Bomberman gameplay screen: owns the shader, the player,
   and every live Bomb -- regardless of who placed it. Bombs are NOT
   owned by Player: a bomb must keep ticking even if the player who
   placed it dies/disconnects, and centralizing them here is what
   makes collision/explosion checks tractable once there are several
   players placing bombs on the same grid. */

class PlayingState : public GameState {
    public:
        PlayingState(Window& window, const QuadMesh& mesh, int gridCols, int gridRows);

        void    handleAction(InputAction action) override;
        void    update(float dt) override;
        void    render() override;

    private:
        Window&            _window;
        const QuadMesh&    _mesh;
        int                _gridCols, _gridRows;
        Shader             _shader;
        Player             _player;         // vector of players ?
        Player             _player2;
        std::vector<Bomb>  _bombs;
};