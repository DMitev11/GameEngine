cmake_minimum_required (VERSION 3.8)
 
if(${BUILD_NAME} MATCHES "Win64")
    set(SRC_FIX win32)
    message(SRC_FIX)
    find_package(OpenGL REQUIRED) 
endif() 

set (HEADER_FILES 
    "inc/Rendering.h" "inc/Model2D.h")

set(SRC_FILES
    "src/${SRC_FIX}/Rendering.cpp")

if(${BUILD_NAME} MATCHES "Win64")
    set(HEADER_FILES
        ${HEADER_FILES}
        "inc/win32/debug/TestRendering.h")
        
    set(SRC_FILES
        ${SRC_FILES}
        "src/win32/debug/TestRendering.cpp")
endif()

add_library (RENDERING STATIC ${HEADER_FILES} ${SRC_FILES} )

set_target_properties(RENDERING 
    PROPERTIES 
    LINKER_LANGUAGE CXX
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/release                                    
) 
 
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
 


target_include_directories(RENDERING PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR} 
    ${PROJECT_SOURCE_DIR}/include/glew-2.1.0/include) 
     
target_link_libraries(RENDERING PUBLIC glfw glm OpenGL::GL glew)   
