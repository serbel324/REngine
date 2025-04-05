cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_STANDARD 23)

set(INCPATH ${PROJECT_SOURCE_DIR}/include)

project(Library)

set(SOURCES
    ext_math.cpp)

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${INCPATH}
)
