cmake_minimum_required (VERSION 3.8)
 
set (HEADER_FILES 
    "inc/Registry.h" "inc/AComponent.h" "inc/Entity.h" "inc/win32/EnttEntity.h"  "inc/ActorEvents.h" "inc/Components/TickComponent.hpp" "inc/Components/IdComponent.h" "inc/Components/RndComponent.hpp" "inc/Components/ActorComponent.hpp")

set (SRC_FILES 
    "src/Entity.cpp" "src/win32/EnttEntity.cpp" "src/Registry.hpp" ) 

add_library (ECS STATIC ${HEADER_FILES} ${SRC_FILES} )

set_target_properties(ECS 
    PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/release                                    
) 
 
target_link_libraries(ECS PUBLIC entt)  
target_include_directories(ECS PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}) 
