cmake_minimum_required(
    VERSION 2.8
    )

project(
    symbolic-regression
    )

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

if( DEBUG_ON )
    set( DEBUG_FLAGS -pg )
endif()

add_definitions(
    -std=c99
    ${DEBUG_FLAGS}
    )

include_directories(
    include
    )

add_executable(
    ${PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/src/main.c
    ${PROJECT_SOURCE_DIR}/src/node.c
    ${PROJECT_SOURCE_DIR}/src/individual.c
    ${PROJECT_SOURCE_DIR}/src/population.c
    )

target_link_libraries( 
    ${PROJECT_NAME}
    m
    ${DEBUG_FLAGS}
    )
