#include "Shader.hpp"
#include <stdexcept>
#include <string>

Shader::Shader(const char* vertexSrc, const char* fragmentSrc) {
    unsigned int vs = compileStage(GL_VERTEX_SHADER, vertexSrc, "vertex");
    unsigned int fs = compileStage(GL_FRAGMENT_SHADER, fragmentSrc, "fragment");

    _program = glCreateProgram();
    glAttachShader(_program, vs);
    glAttachShader(_program, fs);
    glLinkProgram(_program);
    int success;
    glGetProgramiv(_program, GL_LINK_STATUS, &success);
    if (!success) {
        char log[512];
        glGetProgramInfoLog(_program, 512, nullptr, log);
        glDeleteShader(vs);
        glDeleteShader(fs);
        throw std::runtime_error(std::string("Shader link failed: ") + log);
    }
    glDeleteShader(vs);
    glDeleteShader(fs);
}

Shader::~Shader() {
    glDeleteProgram(_program);
}

int Shader::getUniformLocation(const std::string& name) const {
    auto it = _uniformCache.find(name);
    if (it != _uniformCache.end())
        return it->second;
    int loc = glGetUniformLocation(_program, name.c_str());
    _uniformCache.emplace(name, loc);
    return loc;
}

void Shader::setUniform2f(const char* name, float x, float y) const {
    glUniform2f(getUniformLocation(name), x, y);
}

unsigned int Shader::compileStage(unsigned int type, const char* src, const char* stageName) {
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(shader, 512, nullptr, log);
        throw std::runtime_error(std::string("Shader compile failed (") + stageName + "): " + log);
    }
    return shader;
}

void Shader::use() const {
    glUseProgram(_program);
}
