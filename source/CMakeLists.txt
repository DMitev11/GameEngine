# CMakeList.txt : CMake project for GameEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_subdirectory (runtime)

# Add source to this project's executable.
add_executable (GameEngine "GameEngine.cpp" "GameEngine.h" "runtime/reflection/ReflectiveEnumerator.hpp")

# TODO: Add tests and install targets if needed.
find_package(OpenGL REQUIRED)
target_link_libraries(GameEngine PUBLIC ECS glfw glm OpenGL::GL glew)