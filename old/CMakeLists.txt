cmake_minimum_required(VERSION 3.11)
# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Games_Engineering)

#### Setup Directories ####
#Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Ouput all DLLs from all libs into main build folder
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#### Add External Dependencies ####
add_subdirectory("lib/sfml")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

#### Practical 1 ####
file(GLOB_RECURSE SOURCES practical_1/*.cpp practical_1/*.h)
add_executable(PRACTICAL_1 ${SOURCES})
target_include_directories(PRACTICAL_1 PRIVATE ${SFML_INCS})
target_link_libraries(PRACTICAL_1 sfml-graphics)

## Space invaders
file(GLOB_RECURSE SOURCES 2_space_invaders/*.cpp 2_space_invaders/*.h)
add_executable(2_SPACE_INVADERS ${SOURCES} )
target_include_directories(2_SPACE_INVADERS SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(2_SPACE_INVADERS sfml-graphics)

# NEED ALL THIS FOR EACH NEW PROJECT
set_target_properties(2_SPACE_INVADERS 
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)
add_dependencies(2_SPACE_INVADERS copy_resources)
######################################

file(GLOB_RECURSE SOURCES 3_tile_engine/*.cpp 3_tile_engine/*.h)
add_executable(3_TILE_ENGINE ${SOURCES} )
target_include_directories(3_TILE_ENGINE SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(3_TILE_ENGINE lib_tile_level_loader lib_maths sfml-graphics)

# NEED ALL THIS FOR EACH NEW PROJECT
set_target_properties(3_TILE_ENGINE 
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)
add_dependencies(3_TILE_ENGINE copy_resources)
######################################

file(GLOB_RECURSE SOURCES 4_pacman/*.cpp 4_pacman/*.h)
add_executable(4_PACMAN ${SOURCES} )
target_include_directories(3_TILE_ENGINE SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(4_PACMAN lib_tile_level_loader lib_maths sfml-graphics)

# NEED ALL THIS FOR EACH NEW PROJECT
set_target_properties(4_PACMAN 
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)
add_dependencies(4_PACMAN copy_resources)
######################################


add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND} 
  -E copy_directory
    "${PROJECT_SOURCE_DIR}/res"
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res
)
## Tile loader lib
file(GLOB_RECURSE SOURCE_FILES lib_tile_level_loader/*.cpp lib_tile_level_loader/*.h)
add_library(lib_tile_level_loader STATIC ${SOURCE_FILES})
target_include_directories(lib_tile_level_loader INTERFACE "${CMAKE_SOURCE_DIR}/lib_tile_level_loader/" )
target_link_libraries(lib_tile_level_loader lib_maths sfml-graphics)

## Math lib
add_library(lib_maths INTERFACE)
target_sources(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths/maths.h")
target_include_directories(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths" SYSTEM INTERFACE ${SFML_INCS})