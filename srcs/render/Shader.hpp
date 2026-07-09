#pragma once

#include "Gl.hpp"

/* Minimal shader program wrapper: compiles vertex + fragment sources,
   links them, and cleans up on destruction. */

class Shader {
    public:
        Shader(const char* vertexSrc, const char* fragmentSrc);
        ~Shader();
        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;

        void         use() const;
        unsigned int id() const { return _program; }

    private:
        unsigned int compileStage(unsigned int type, const char* src, const char* stageName);

        unsigned int _program;
};
