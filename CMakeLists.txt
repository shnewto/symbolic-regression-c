cmake_minimum_required(
    VERSION 2.8
    )

project(
    symbolic-regression
    )

add_definitions(
    -std=c99 
    -p
    -g
    )

include_directories(
    include
    )

add_executable(
    ${PROJECT_NAME}
    src/main.c
    src/node.c
    src/individual.c
    src/population.c
    )

target_link_libraries( 
    ${PROJECT_NAME}
    m 
    )