#pragma once

#include "Gl.hpp"

/* Player lives on a discrete grid (classic Bomberman movement).
   Grid origin (0,0) is top-left; NDC conversion happens internally
   so the rest of the game can just think in grid cells. */

/* Most of this probably should exist in an entity interface if we are 
   planning to add more */

class Player {
    public:
        Player(int gridX, int gridY, int gridCols, int gridRows);
        ~Player();
        Player(const Player&) = delete;
        Player& operator=(const Player&) = delete;

        void move(int dx, int dy);
        void render(unsigned int shaderProgram) const;

        int gridX() const { return _gridX; }
        int gridY() const { return _gridY; }

    private:
        void setupMesh();
        void updateOffset();

        unsigned int _vao = 0, _vbo = 0, _ebo = 0;

        int   _gridX, _gridY;
        int   _gridCols, _gridRows;
        float _offsetX = 0.0f, _offsetY = 0.0f;
        float _scaleX, _scaleY;
};
