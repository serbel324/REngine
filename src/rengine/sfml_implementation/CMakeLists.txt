cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_STANDARD 23)

set(INCPATH ${PROJECT_SOURCE_DIR}/include)

project(REngineSFMLImplementation)

set(SOURCES
    sfml_frame.cpp
    sfml_graphics.cpp
    sfml_input.cpp)

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${INCPATH}
)

target_link_libraries(${PROJECT_NAME}
    REngineCore
)