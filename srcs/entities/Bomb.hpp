#pragma once

#include "Gl.hpp"
#include "render/QuadMesh.hpp"
#include "entities/Player.hpp"

class Bomb {
    public:
        Bomb(const QuadMesh& mesh, int gridX, int gridY, int gridCols, int gridRows,
             Player& player, float fuseSeconds = 3.0f);

        void    update(float dt);
        void    render(unsigned int shaderProgram) const;
        bool    hasExploded() const { return _fuseRemaining <= 0.0f; }
        int     gridX() const { return _gridX; }
        int     gridY() const { return _gridY; }
        Player* owner() const { return _owner; }

    private:
        // Stored as a pointer (not a reference) so Bomb stays movable --
        // std::vector<Bomb>::erase needs move-assignment, and a
        // reference member makes that impossible to generate. The
        // constructor still takes a reference, so a caller can never
        // pass null in the first place.
        const QuadMesh* _mesh;

        int   _gridX, _gridY;
        float _offsetX, _offsetY;
        float _scaleX, _scaleY;
        Player* _owner;
        float _fuseRemaining;
};