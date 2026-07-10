#include "PlayingState.hpp"

namespace {
    const char* kVertexShaderSrc = R"glsl(
        #version 330 core
        layout(location = 0) in vec2 aPos;

        uniform vec2 uOffset;
        uniform vec2 uScale;

        void main() {
            gl_Position = vec4(aPos * uScale + uOffset, 0.0, 1.0);
        }
    )glsl";

    const char* kFragmentShaderSrc = R"glsl(
        #version 330 core
        out vec4 FragColor;

        void main() {
            FragColor = vec4(1.0, 1.0, 1.0, 1.0);
        }
    )glsl";
}

PlayingState::PlayingState(Window& window, const QuadMesh& mesh, int gridCols, int gridRows)
    : _window(window),
      _mesh(mesh),
      _gridCols(gridCols),
      _gridRows(gridRows),
      _shader(kVertexShaderSrc, kFragmentShaderSrc),
      _player(mesh, gridCols / 2, gridRows / 2, gridCols, gridRows),
      _player2(mesh, gridCols / 2.5, gridRows / 2, gridCols, gridRows)
{}

void PlayingState::handleAction(InputAction action) {
    switch (action) {
        case InputAction::MoveUp:    _player.move(0, -1); break;
        case InputAction::MoveDown:  _player.move(0, 1);  break;
        case InputAction::MoveLeft:  _player.move(-1, 0); break;
        case InputAction::MoveRight: _player.move(1, 0);  break;
        case InputAction::PlaceBomb:
            if (_player.canPlaceBomb()) {
                _bombs.emplace_back(_mesh, _player.gridX(), _player.gridY(),
                                     _gridCols, _gridRows, _player);
                _player.onBombPlaced();
            }
            break;
        case InputAction::MoveUpP2:     _player2.move(0, -1); break;
        case InputAction::MoveDownP2:   _player2.move(0, 1);  break;
        case InputAction::MoveLeftP2:   _player2.move(-1, 0); break;
        case InputAction::MoveRightP2:  _player2.move(1, 0);  break;
        case InputAction::PlaceBombP2:
            if (_player2.canPlaceBomb()) {
                _bombs.emplace_back(_mesh, _player2.gridX(), _player2.gridY(),
                                     _gridCols, _gridRows, _player2);
                _player2.onBombPlaced();
            }
            break;
        case InputAction::Quit:      _window.close();     break;

        default: break;
    }
}

void PlayingState::update(float dt) {
    for (auto& bomb : _bombs)
        bomb.update(dt);

    for (auto it = _bombs.begin(); it != _bombs.end(); ) {
        if (it->hasExploded()) {
            it->owner()->onBombExploded();
            // bomb deal damage
            it = _bombs.erase(it);
        } else {
            ++it;
        }
    }
}

void PlayingState::render() {
    _shader.use();
    _player.render(_shader.id());
    _player2.render(_shader.id());
    for (const auto& bomb : _bombs)
        bomb.render(_shader.id());
}