#pragma once

#include "Gl.hpp"

/* Single shared unit quad (centered at origin, size 1x1), reused by
   every quad-shaped entity (player, bombs, tiles, enemies...).
   Create exactly ONE instance (in main / a Game/App class) and pass
   entities a const reference. Entities own their own transform
   (offset/scale) but never their own VAO/VBO/EBO. */

class QuadMesh {
    public:
        QuadMesh();
        ~QuadMesh();
        QuadMesh(const QuadMesh&) = delete;
        QuadMesh& operator=(const QuadMesh&) = delete;

        void    draw() const;

    private:
        unsigned int _vao = 0, _vbo = 0, _ebo = 0;
};