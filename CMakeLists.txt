cmake_minimum_required (VERSION 2.6)

project (SdlWidgets)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wno-unused-parameter") # warning level
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") # ensure C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g") # add debug symbols even in release

file(GLOB sources src/*.cpp SDL_gfx/*.cpp)
file(GLOB headers src/*.hpp SDL_gfx/*.h)

INCLUDE_DIRECTORIES(.)

add_executable(SdlWidgets ${sources} ${headers})

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} SDL2_gfx SDL2_ttf SDL2_image SDL2_mixer)

