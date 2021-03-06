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
add_executable(examples ${EXAMPLES_SOURCE_FILES})
add_executable(maze ${MAZE_SOURCE_FILES})

set_target_properties(graphs PROPERTIES LINKER_LANGUAGE CXX)

find_package(
  Boost 1.71
  COMPONENTS system program_options
  REQUIRED)

target_link_libraries(examples
    graphs
    pthread
    ${Boost_LIBRARIES}
    )
target_link_libraries(maze
    graphs
    pthread
    ${Boost_LIBRARIES}
    )

add_custom_target(clangformat COMMAND clang-format -style=WebKit -i ${DIJKSTRA_SOURCE_FILES} ${KRUSKAL_SOURCE_FILES} ${PRIM_SOURCE_FILES} ${EXAMPLES_SOURCE_FILES} ${GRAPHS_HEADER_FILES})
