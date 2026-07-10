#include "Player.hpp"

Player::Player(const QuadMesh& mesh, int gridX, int gridY, int gridCols, int gridRows)
    : _mesh(mesh), _gridX(gridX), _gridY(gridY), _gridCols(gridCols), _gridRows(gridRows)
{
    _scaleX = 2.0f / static_cast<float>(gridCols);
    _scaleY = 2.0f / static_cast<float>(gridRows);
    updateOffset();
}

void Player::updateOffset() {
    // Flip Y: grid row 0 is the top of the screen, NDC +1 is the top.
    _offsetX = -1.0f + _scaleX * (static_cast<float>(_gridX) + 0.5f);
    _offsetY =  1.0f - _scaleY * (static_cast<float>(_gridY) + 0.5f);
}

void Player::move(int dx, int dy) {
    int newX = _gridX + dx;
    int newY = _gridY + dy;
    if (newX < 0 || newX >= _gridCols) return;
    if (newY < 0 || newY >= _gridRows) return;
    _gridX = newX;
    _gridY = newY;
    updateOffset();
}

void Player::render(unsigned int shaderProgram) const {
    int offsetLoc = glGetUniformLocation(shaderProgram, "uOffset");
    int scaleLoc  = glGetUniformLocation(shaderProgram, "uScale");

    glUniform2f(offsetLoc, _offsetX, _offsetY);
    // 0.9x padding so a grid/wall border would still be visible around it later.
    glUniform2f(scaleLoc, _scaleX * 0.9f, _scaleY * 0.9f);
    _mesh.draw();
}