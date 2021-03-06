set(EXAMPLES_SOURCE_FILES
    "${PROJECT_SRC_DIR}/examples.cpp"
    )
set(MAZE_SOURCE_FILES
    "${PROJECT_SRC_DIR}/maze.cpp"
    )

set(GRAPHS_HEADER_FILES
    "${PROJECT_HEADER_DIR}/graph.h"
    "${PROJECT_HEADER_DIR}/kruskal.h"
    "${PROJECT_HEADER_DIR}/prim.h"
    "${PROJECT_HEADER_DIR}/dijkstra.h"
    "${PROJECT_HEADER_DIR}/dfs.h"
    "${PROJECT_HEADER_DIR}/bfs.h"
    "${PROJECT_HEADER_DIR}/maze.h"
    )

configure_file(
    "${PROJECT_CONFIG_DIR}/config.h"
    "${CMAKE_CURRENT_BINARY_DIR}/defaults.h"
    )
