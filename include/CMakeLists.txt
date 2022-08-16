# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8) 
 
add_subdirectory ("entt") 
add_subdirectory ("glfw-3.3.7") 
add_subdirectory ("glm")  
add_subdirectory ("glew-2.1.0/build/cmake")   
  
target_include_directories(glew PUBLIC ${PROJECT_SOURCE_DIR}/include/glew-2.1.0/include)
 
  