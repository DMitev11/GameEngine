# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("GameEngine" LANGUAGES CXX)


# Include sub-projects.
# Info tread - https://stackoverflow.com/questions/45688522/how-to-enable-c17-in-cmake
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
add_subdirectory ("source") 
add_subdirectory ("include")

 
