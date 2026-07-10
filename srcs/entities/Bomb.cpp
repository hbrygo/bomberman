#include "Bomb.hpp"

Bomb::Bomb(const QuadMesh& mesh, int gridX, int gridY, int gridCols, int gridRows, Player& player, float fuseSeconds)
    : _mesh(&mesh), _gridX(gridX), _gridY(gridY), _owner(&player), _fuseRemaining(fuseSeconds)
{
    _scaleX = 2.0f / static_cast<float>(gridCols);
    _scaleY = 2.0f / static_cast<float>(gridRows);
    _offsetX = -1.0f + _scaleX * (static_cast<float>(gridX) + 0.5f);
    _offsetY =  1.0f - _scaleY * (static_cast<float>(gridY) + 0.5f);
}

void Bomb::update(float dt) {
    _fuseRemaining -= dt;
}

void Bomb::render(unsigned int shaderProgram) const {
    int offsetLoc = glGetUniformLocation(shaderProgram, "uOffset");
    int scaleLoc  = glGetUniformLocation(shaderProgram, "uScale");

    glUniform2f(offsetLoc, _offsetX, _offsetY);
    // Slightly smaller than a full tile so it visually reads as an
    // object sitting on the grid rather than filling it.
    glUniform2f(scaleLoc, _scaleX * 0.7f, _scaleY * 0.7f);

    _mesh->draw();
}