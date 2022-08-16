# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("GameEngine" LANGUAGES CXX)  
# Include sub-projects.
# Info tread - https://stackoverflow.com/questions/45688522/how-to-enable-c17-in-cmake

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17") 
set(BUILD_TYPE_WIN Win64)
add_subdirectory ("source") 
add_subdirectory ("include")


if(${BUILD_NAME} MATCHES "Win64")  
    file(COPY ${CMAKE_SOURCE_DIR}/include/glew-2.1.0/bin/Debug/x64/glew32d.dll
    DESTINATION
    ${CMAKE_SOURCE_DIR}/out/build/x64-Debug/source) 
endif() 
   