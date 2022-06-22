# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8) 

add_subdirectory ("entt") 

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory ("glfw-3.3.7") 
add_subdirectory ("glm")  
add_subdirectory ("glew-2.1.0/build/cmake")  

include_directories(
    glfw-3.3.7/include/GLFW
    glm/glm
    glew-2.1.0/include
)
 