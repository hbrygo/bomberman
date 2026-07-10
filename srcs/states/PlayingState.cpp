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
      _shader(kVertexShaderSrc, kFragmentShaderSrc),
      _player(mesh, gridCols / 2, gridRows / 2, gridCols, gridRows),
      _player2(mesh, gridCols / 1.5, gridRows / 2, gridCols, gridRows)
{
}

void PlayingState::handleAction(InputAction action) {
    switch (action) {
        case InputAction::MoveUp:       _player.move(0, -1); break;
        case InputAction::MoveDown:     _player.move(0, 1);  break;
        case InputAction::MoveLeft:     _player.move(-1, 0); break;
        case InputAction::MoveRight:    _player.move(1, 0);  break;
        case InputAction::MoveUpP2:     _player2.move(0, -1); break;
        case InputAction::MoveDownP2:   _player2.move(0, 1);  break;
        case InputAction::MoveLeftP2:   _player2.move(-1, 0); break;
        case InputAction::MoveRightP2:  _player2.move(1, 0);  break;
        case InputAction::Quit:         _window.close();     break;
        default: break; // PlaceBomb etc. not implemented yet
    }
}

void PlayingState::update(float dt) {
    (void)dt; // nothing time-based yet (no animations/bomb timers)
}

void PlayingState::render() {
    _shader.use();
    _player.render(_shader.id());
    _player2.render(_shader.id());
}