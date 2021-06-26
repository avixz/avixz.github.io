cmake_minimum_required(VERSION 3.19)
project(SDL2Game)

set(CMAKE_CXX_STANDARD 17)

if ("${PLATFORM}" STREQUAL "EMSCRIPTEN")
    message("Using emscripten!")
    set(USE_FLAGS "-DEMSCRIPTEN -s USE_SDL=2 -s USE_FREETYPE=1 \
                   --shell-file /usr/share/emscripten/src/shell_minimal.html")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXECUTABLE_SUFFIX .html)
else()
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
endif()

add_executable(SDL2Game main.cpp Game.h Game.cpp)
target_link_libraries(SDL2Game ${SDL2_LIBRARIES})
