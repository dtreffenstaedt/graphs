cmake_minimum_required(VERSION 3.10)
project(graphs LANGUAGES CXX)

set(PROJECT_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(PROJECT_HEADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(PROJECT_CONFIG_DIR "${CMAKE_CURRENT_SOURCE_DIR}/config")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/output/bin")

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/version.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/files.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/compile_options.cmake")

include_directories(
    ${PROJECT_HEADER_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    )

add_library(graphs OBJECT ${GRAPHS_HEADER_FILES})
add_executable(dijkstra ${DIJKSTRA_SOURCE_FILES})
add_executable(prim ${PRIM_SOURCE_FILES})

set_target_properties(graphs PROPERTIES LINKER_LANGUAGE CXX)


target_link_libraries(dijkstra
    graphs
    )

target_link_libraries(prim
    graphs
    )

add_custom_target(clangformat COMMAND clang-format -style=WebKit -i ${DIJKSTRA_SOURCE_FILES} ${PRIM_SOURCE_FILES} ${GRAPHS_HEADER_FILES})
