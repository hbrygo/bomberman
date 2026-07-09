#pragma once

#include <GLFW/glfw3.h>
#include "Window.hpp"
#include "../entities/Player.hpp"

class GlfwInputHandler {
    public:
        GlfwInputHandler(Window& window) : _window(window), _player(nullptr) {}

        void setup() {
            _window.setUserPointer(this);
            _window.setKeyCallback([](GLFWwindow* win, int key, int, int action, int) {
                static_cast<GlfwInputHandler*>(
                    glfwGetWindowUserPointer(win))->onKey(key, action);
            });
        }

		void setPlayer(Player *player) { _player = player; }

        void onKey(int key, int action) {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
                _window.close();
                return;
            }
            if (!_player)
				return;
            // Grid-step movement: only react to the initial press, not
            // GLFW_REPEAT, so holding a key doesn't fire multiple moves.
			if (action != GLFW_PRESS)
				return;
            switch (key) {
                case GLFW_KEY_W: _player->move(0, -1); break;
                case GLFW_KEY_S: _player->move(0, 1);  break;
                case GLFW_KEY_A: _player->move(-1, 0); break;
                case GLFW_KEY_D: _player->move(1, 0);  break;
            }
        }

    private:
        Window&		_window;
		Player*		_player;
};