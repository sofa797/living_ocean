# simulation Living Ocean

Ocean simulation is a marine ecosystem simulation written in C++ using the **SFML** library. The project models the interactions between various ocean creatures such as aquatics, herbivores, and predators.

## Features
- Algae grow and reproduce.
- Herbivorous fish feed on algae and reproduce when sufficiently satiated.
- Predators hunt herbivores and also reproduce.
- The entire simulation is rendered using SFML.

## Building the project
### Requirements
- **CMake** >= 3.16
- **Компилятор** GCC 13.1.0 (MinGW-w64 64-bit)
- **SFML** 2.6.1 (compatible build with your compiler)

### Assembly instructions (Windows)

1. Download and unzip SFML for MinGW 13.1.0 (64-bit).
2. Make sure the path to SFML is correctly specified in `CMakeLists.txt`:
   ```cmake
   set(CMAKE_PREFIX_PATH "C:/Users/Sofia/Downloads/SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit/SFML-2.6.1")
   set(SFML_DIR "C:/Users/Sofia/Downloads/SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit/SFML-2.6.1/lib/cmake/SFML")```
3. Create a folder for the build:
```mkdir build
cd build
```
4. Generate build files using CMake:
```$ cmake -S . -B build -G "MinGW Makefiles"
```
5. Build the project with mingw32-make:
```$ mingw32-make -C build```
6. Run the simulation:
``` ./build/OceanSimulation.exe```
