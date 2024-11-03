cmake_minimum_required(VERSION 3.14)
project(dm50)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

# Download enable
include(FetchContent)

# SDL2 Version
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.30.9
)

# Descarga e incorpora SDL2
FetchContent_MakeAvailable(SDL2)

include_directories(${SDL2_SOURCE_DIR}/include)

# Crear la biblioteca estática de SDL2
add_library(SDL2-static STATIC IMPORTED)
set_target_properties(SDL2-static PROPERTIES
    IMPORTED_LOCATION "${SDL2_BINARY_DIR}/libSDL2.a"
    INTERFACE_INCLUDE_DIRECTORIES "${SDL2_SOURCE_DIR}/include"
)

# Agrega tus archivos fuente
add_executable(TuEjecutable main.c)

# Enlaza SDL2 con tu ejecutable
target_link_libraries(TuEjecutable SDL2-static)
