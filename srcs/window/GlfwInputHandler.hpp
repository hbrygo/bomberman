#pragma once

#include <GLFW/glfw3.h>
#include "Window.hpp"

class GlfwInputHandler {
    public:
        GlfwInputHandler(Window& window) : _window(window){}

        void setup() {
            _window.setUserPointer(this);
            _window.setKeyCallback([](GLFWwindow* win, int key, int, int action, int) {
                static_cast<GlfwInputHandler*>(
                    glfwGetWindowUserPointer(win))->onKey(key, action);
            });
        }

        void onKey(int key, int action) {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
                _window.close();
			// handleKey(key, action);
        }

        void poll() {
            GLFWwindow *win = _window.window;

            if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS) printf("move up\n"); 
            if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS) printf("move down\n"); 
            if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS) printf("move left\n"); 
            if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS) printf("move right\n"); 
        }

    private:
        Window&  _window;
};