cmake_minimum_required(VERSION 3.8)

set(HEADER_FILES 
    "ReflectiveEnumerator.hpp")

add_library(REFLECTION STATIC ${HEADER_FILES})

set_target_properties(REFLECTION 
    PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/release                                    
) 

target_include_directories(REFLECTION PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}) 
