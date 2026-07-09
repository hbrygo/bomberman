#include "Player.hpp"

namespace {
    constexpr float kQuadVerts[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f,
    };
    constexpr unsigned int kQuadIndices[] = { 0, 1, 2, 2, 3, 0 };
}

Player::Player(int gridX, int gridY, int gridCols, int gridRows)
    : _gridX(gridX), _gridY(gridY), _gridCols(gridCols), _gridRows(gridRows)
{
    _scaleX = 2.0f / static_cast<float>(gridCols);
    _scaleY = 2.0f / static_cast<float>(gridRows);
    setupMesh();
    updateOffset();
}

Player::~Player() {
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_ebo);
    glDeleteVertexArrays(1, &_vao);
}

void Player::setupMesh() {		// very basic openGL mesh (hardcoded square)
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glGenBuffers(1, &_ebo);
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(kQuadVerts), kQuadVerts, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(kQuadIndices), kQuadIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
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

    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
