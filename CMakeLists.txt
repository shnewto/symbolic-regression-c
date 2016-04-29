cmake_minimum_required(
    VERSION 2.8
)

#if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
#    message( 
#        FATAL_ERROR 
#        "in-source builds disabled. \n"
#        " CMakeCache.txt."
#    )
#    rm -rf CMakeCache.txt
#endif()

project(
    symbolic-regression
)

if( DEBUG_ON )
    set( DEBUG_FLAGS -pg )
endif()

FILE( 
    GLOB 
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h 
) 

FILE( 
    GLOB 
    SRCS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c INCLUDES
) 

FILE( 
    GLOB 
    TEST_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/test/*.c 
)

SET(
    SRC_LIB
    symbolic-regression-lib
)

SET(
    CMAKE_LIBRARY_OUTPUT_DIRECTORY 
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

set(
    CMAKE_ARCHIVE_OUTPUT_DIRECTORY 
    ${CMAKE_CURRENT_SOURCE_DIR}/lib 
    )

SET(
    CMAKE_RUNTIME_OUTPUT_DIRECTORY 
    ${CMAKE_CURRENT_SOURCE_DIR}/bin
)

SET( 
    INCLUDE_DIR 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
) 

SET( 
    TEST_LIB 
    test-symbolic-regression-c 
)

SET(
    TEST_LIB_NAME
    lib${TEST_LIB}.so
)

include_directories(
    ${INCLUDE_DIR}
)

add_library(
    ${TEST_LIB}
    SHARED
    ${TEST_SRCS}
)

add_library(
    ${SRC_LIB}
    STATIC
    ${SRCS}
)

#set_target_properties( 
#    ${SRC_LIB} PROPERTIES
#    LIBRARY_OUTPUT_DIRECTORY 
#    ${CMAKE_CURRENT_SOURCE_DIR}/lib 
#)
#
#set_target_properties( 
#    ${TEST_LIB} PROPERTIES
#    LIBRARY_OUTPUT_DIRECTORY 
#    ${CMAKE_CURRENT_SOURCE_DIR}/lib 
#)

add_definitions(
    -std=c99
    -fPIC
    ${DEBUG_FLAGS}
)

add_executable(
    ${PROJECT_NAME}
    ${SRCS}
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${INCLUDE_DIR}    
)

target_link_libraries( 
    ${PROJECT_NAME}
    m
    ${DEBUG_FLAGS}
    -fPIC
)

target_include_directories(
    ${TEST_LIB}
    PUBLIC
    ${INCLUDE_DIR}    
    -fPIC
)

target_link_libraries( 
    ${TEST_LIB}
    ${SRC_LIB}
    cgreen
)

SET(
    EXE_ARG_0 cgreen-runner
)

SET(
    EXE_ARG_1 --colours
)

SET(
    EXE_ARG_2 ${CMAKE_CURRENT_SOURCE_DIR}/lib/${TEST_LIB_NAME};
)

#    cgreen-runner --colours ${CMAKE_CURRENT_SOURCE_DIR}/lib/${TEST_LIB_NAME}

add_custom_target(
    test 
#    COMMAND 
    execute_process(
    COMMAND ${EXE_ARG_0} ${EXE_ARG_1} ${EXE_ARG_2}
    )
)

