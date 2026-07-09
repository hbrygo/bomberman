// #include <bomberman.hpp>
#include "window/Window.hpp"
#include "window/GlfwInputHandler.hpp"
#include "render/Shader.hpp"
#include "entities/Player.hpp"

namespace {
    constexpr int kGridCols = 15;
    constexpr int kGridRows = 13;

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

int main(int argc, char **argv) {
    (void)argv;
    try {
        if (argc > 1) {
            throw std::runtime_error("Usage: ./bomberman");
        }

        Window              w;
        GlfwInputHandler    input(w);
        input.setup();

        Shader shader(kVertexShaderSrc, kFragmentShaderSrc);
        Player player(kGridCols / 2, kGridRows / 2, kGridCols, kGridRows);
        input.setPlayer(&player);

        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);

        while (!w.shouldClose()) {
            w.pollEvents();

            glClear(GL_COLOR_BUFFER_BIT);
            shader.use();
            player.render(shader.id());
            w.swapBuffers();
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return (1);
    }
    return 0;
}
