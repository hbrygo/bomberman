
# Build Instructions

## Requirements

Before building the project, make sure you have:

- C++20 compatible compiler (`c++`)
- `make`
- `cmake`
- OpenGL development libraries
- `pthread`
- `dl`

The project automatically builds the bundled GLFW library located in `libs/glfw`.

## Build 

```
# Clone the repository
git clone --recurse https://github.com/hbrygo/bomberman.git
cd bomberman

# Compile the project
make
```

## Available Make Targets

| Command | Description |
|---------|-------------|
| `make` or `make all` | Build GLFW (if needed) and compile the project. |
| `make clean` | Remove all object files and the `build/` directory. |
| `make fclean` | Remove object files, executable, and the generated GLFW build directory. |
| `make re` | Perform a full clean and rebuild everything. |
| `make san` | Build with AddressSanitizer, LeakSanitizer, and UndefinedBehaviorSanitizer enabled for debugging. |
| `make valgrind` | Build the project and run it through Valgrind with full leak checking. |

## Configuration

The project is compiled using:

- **Compiler:** `c++`
- **Standard:** `C++20`
- **Warnings:** `-Wall -Wextra -Werror`
- **Debug symbols:** `-g`

## Notes

- GLFW is automatically configured and built with CMake the first time the project is compiled.
- Dependency files (`.d`) are generated automatically for incremental builds.
- Sanitizer builds are intended for debugging only and may reduce performance.
- `make valgrind` requires Valgrind to be installed on your system.
