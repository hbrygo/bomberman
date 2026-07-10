// #include <bomberman.hpp>
#include <memory>
#include "window/Window.hpp"
#include "window/GlfwInputHandler.hpp"
#include "render/QuadMesh.hpp"
#include "core/App.hpp"
#include "states/PlayingState.hpp"

namespace {
    constexpr int kGridCols = 15;
    constexpr int kGridRows = 13;
}

int main(int argc, char **argv) {
    (void)argv;
    try {
        if (argc > 1) {
            throw std::runtime_error("Usage: ./bomberman");
        }

        Window           w;
        GlfwInputHandler input(w);
        input.setup();

        QuadMesh quadMesh; // shared by every quad-shaped entity

        App app;
        input.setActionCallback([&app](InputAction action) { app.handleAction(action); });

        // Straight into gameplay for now; swap this for a
        // MainMenuState once the menu exists.
        app.changeState(std::make_unique<PlayingState>(w, quadMesh, kGridCols, kGridRows));

        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);

        while (!w.shouldClose()) {
            w.pollEvents();
            app.update(0.0f); // placeholder until entities need real delta time
            glClear(GL_COLOR_BUFFER_BIT);
            app.render();
            w.swapBuffers();
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return (1);
    }
    return 0;
}