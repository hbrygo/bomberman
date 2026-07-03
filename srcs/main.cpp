#include <bomberman.hpp>
#include "window/Window.hpp"
#include "window/GlfwInputHandler.hpp"

int main(int argc, char **argv) {
	(void)argv;
	try {
		if (argc > 1) {
			throw std::runtime_error("Usage: ./bomberman");
		}
		// Game game;
		Window				w;
		GlfwInputHandler	input(w);
		input.setup();
		while (!w.shouldClose()) { 
			input.poll();
			w.pollEvents();
		}
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return (1);
	}
    return 0;
}