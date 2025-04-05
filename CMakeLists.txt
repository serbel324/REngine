cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE Debug)

project(REngine)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

add_subdirectory(app)
add_subdirectory(src)
