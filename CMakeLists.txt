cmake_minimum_required(VERSION 3.16)
project(OceanSimulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_PREFIX_PATH "C:/Users/Sofia/Downloads/SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit/SFML-2.6.1")

set(SFML_USE_STATIC_LIBRARIES FALSE)
set(SFML_STATIC_LIBRARIES FALSE)
set(SFML_DIR "C:/Users/Sofia/Downloads/SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit/SFML-2.6.1/lib/cmake/SFML")
set(SFML_DEBUG_POSTFIX "")

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/ocean.cpp
    ${CMAKE_SOURCE_DIR}/src/algae.cpp
    ${CMAKE_SOURCE_DIR}/src/herbivore.cpp
    ${CMAKE_SOURCE_DIR}/src/predator.cpp
    ${CMAKE_SOURCE_DIR}/src/fish.cpp
)

add_executable(OceanSimulation ${SOURCES})

include_directories(${CMAKE_SOURCE_DIR}/include)

target_link_libraries(OceanSimulation sfml-graphics sfml-window sfml-system)