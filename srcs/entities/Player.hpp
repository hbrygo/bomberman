#pragma once

#include "Gl.hpp"
#include "render/QuadMesh.hpp"

/* Player lives on a discrete grid (classic Bomberman movement).
   Grid origin (0,0) is top-left; NDC conversion happens internally
   so the rest of the game can just think in grid cells.

   Player no longer owns any GL buffers: it draws itself using a
   shared QuadMesh passed in at construction, and just uploads its
   own offset/scale uniforms before drawing. */

/* Most of this probably should exist in an entity interface if we are
   planning to add more */

class Player {
    public:
        Player(const QuadMesh& mesh, int gridX, int gridY, int gridCols, int gridRows);
        ~Player() = default;
        Player(const Player&) = delete;
        Player& operator=(const Player&) = delete;

        void    move(int dx, int dy);
        void    render(unsigned int shaderProgram) const;

        int     gridX() const { return _gridX; }
        int     gridY() const { return _gridY; }

        // Bomb-count rule: how many the player is allowed to have live
        // at once. Player only tracks the COUNT 
        // it never owns the actual Bomb objects
        // PlayingState does (see Bomb.hpp).
        bool    canPlaceBomb() const  { return _activeBombs < _maxBombs; }
        void    onBombPlaced()        { ++_activeBombs; }
        void    onBombExploded()      { if (_activeBombs > 0) --_activeBombs; }

    private:
        void    updateOffset();

        // See Bomb.hpp for why this is a pointer, not a reference.
        const QuadMesh* _mesh;

        int     _gridX, _gridY;
        int     _gridCols, _gridRows;
        float   _offsetX = 0.0f, _offsetY = 0.0f;
        float   _scaleX, _scaleY;

        int     _maxBombs   = 1;
        int     _activeBombs = 0;
};