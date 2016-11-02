CMAKE_MINIMUM_REQUIRED(
    VERSION 2.8
)

PROJECT(
    symbolic-regression-c
)

# cmake .. -DDEBUG_ON=true
IF( DEBUG_ON )
    SET( DEBUG_FLAGS -pg )
ENDIF()

FILE( 
    GLOB 
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h 
) 

FILE( 
    GLOB 
    SRCS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c INCLUDES
) 


SET(
    SRC_LIB
    symbolic-regression
)

SET(
    MTWIST_LIB
    mtwist
)

SET(
    CMAKE_LIBRARY_OUTPUT_DIRECTORY 
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

SET(
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
    DEP_INCLUDE_DIR 
    ${CMAKE_CURRENT_SOURCE_DIR}/dep/include
) 

INCLUDE_DIRECTORIES(
    ${INCLUDE_DIR}
    ${DEP_INCLUDE_DIR}
)

ADD_LIBRARY(
    ${MTWIST_LIB}
    ${CMAKE_CURRENT_SOURCE_DIR}/dep/src/mtwist.c
)

ADD_LIBRARY(
    ${SRC_LIB}
    SHARED
    ${SRCS}
)

ADD_DEFINITIONS(
    -std=c99
    -fPIC
    ${DEBUG_FLAGS}
)

ADD_EXECUTABLE(
    ${PROJECT_NAME}
    ${SRCS}
)

TARGET_INCLUDE_DIRECTORIES(
    ${PROJECT_NAME}
    PUBLIC
    ${INCLUDE_DIR}    
    ${DEP_INCLUDE_DIR}
)

TARGET_LINK_LIBRARIES( 
    ${PROJECT_NAME}
    m
    ${MTWIST_LIB}
    ${DEBUG_FLAGS}
    -fPIC
)

ADD_CUSTOM_TARGET(
        test-suite
        DEPENDS ${PROJECT_NAME}
)

FILE(
        GLOB
        TEST_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/test/*.c
)

FOREACH(TEST_SOURCE_FILE ${TEST_SRCS})
    GET_FILENAME_COMPONENT(
        TEST_FILE_NAME
        ${TEST_SOURCE_FILE}
        NAME_WE
    )

    LIST(
        APPEND
        TEST_LIBS
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/lib${TEST_FILE_NAME}.so
    )

    ADD_LIBRARY(
        ${TEST_FILE_NAME}
        SHARED
        EXCLUDE_FROM_ALL
        ${TEST_SOURCE_FILE} 
    )

    ADD_DEPENDENCIES(
        test-suite
        ${TEST_FILE_NAME}
    )

    TARGET_INCLUDE_DIRECTORIES(
        ${TEST_FILE_NAME}
        PUBLIC
        ${INCLUDE_DIR}    
        ${DEP_INCLUDE_DIR}
    )
    TARGET_LINK_LIBRARIES( 
        ${TEST_FILE_NAME}
        ${SRC_LIB}
        ${MTWIST_LIB}
        cgreen
    )
ENDFOREACH()


# run unit tests
ADD_CUSTOM_COMMAND(
        TARGET test-suite
        POST_BUILD
        COMMAND
        cgreen-runner --colours ${TEST_LIBS}
)