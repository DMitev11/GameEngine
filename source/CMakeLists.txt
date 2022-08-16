# CMakeList.txt : CMake project for GameEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_subdirectory (runtime) 
file( COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets
    DESTINATION ${CMAKE_SOURCE_DIR}/out/build/x64-Debug/source/
)
# Add source to this project's executable.
add_executable (GameEngine "GameEngine.cpp" "GameEngine.h")

# TODO: Add tests and install targets if needed. 
target_link_libraries(GameEngine PUBLIC ECS RENDERING)
# https://stackoverflow.com/questions/13429656/how-to-copy-contents-of-a-directory-into-build-directory-after-make-with-cmake
add_custom_command(
    TARGET ${PROJECT_NAME} PRE_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/source/assets/" 
    "${CMAKE_SOURCE_DIR}/out/build/${CONFIGURATION_NAME}/source/assets/"
)
