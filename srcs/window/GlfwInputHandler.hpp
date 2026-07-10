#pragma once

#include <functional>
#include <GLFW/glfw3.h>
#include "window/Window.hpp"
#include "input/KeyBindings.hpp"
#include "input/InputAction.hpp"

/* Translates raw GLFW key events into abstract InputActions via
   KeyBindings, then forwards them through a callback. Deliberately
   knows nothing about Player, GameState, or any other concrete
   gameplay type -- whoever sets the callback (App, in main) decides
   what an action means. */

class GlfwInputHandler {
    public:
        using ActionCallback = std::function<void(InputAction)>;

        GlfwInputHandler(Window& window) : _window(window) {}

        void    setup() {
            _window.setUserPointer(this);
            _window.setKeyCallback([](GLFWwindow* win, int key, int, int action, int) {
                static_cast<GlfwInputHandler*>(
                    glfwGetWindowUserPointer(win))->onKey(key, action);
            });
        }

        void    setActionCallback(ActionCallback cb) { _callback = std::move(cb); }

        // Exposed so a future settings menu can rebind keys directly:
        // input.bindings().bind(newKey, InputAction::MoveUp);
        KeyBindings&    bindings() { return _bindings; }

    private:
        void    onKey(int key, int action) {
            // Discrete step per press only: ignore GLFW_REPEAT and
            // GLFW_RELEASE so holding or releasing a key doesn't
            // re-trigger a grid step or fire an action twice.
            if (action != GLFW_PRESS)
                return;

            InputAction mapped;
            if (_bindings.resolve(key, mapped) && _callback)
                _callback(mapped);
        }

        Window&        _window;
        KeyBindings    _bindings;
        ActionCallback _callback;
};