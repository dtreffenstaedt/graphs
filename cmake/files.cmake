set(DIJKSTRA_SOURCE_FILES
    "${PROJECT_SRC_DIR}/dijkstra.cpp"
    )

set(PRIM_SOURCE_FILES
    "${PROJECT_SRC_DIR}/prim.cpp"
    )

set(GRAPHS_HEADER_FILES
    "${PROJECT_HEADER_DIR}/graph.h"
    "${PROJECT_HEADER_DIR}/tree.h"
    )

configure_file(
    "${PROJECT_CONFIG_DIR}/config.h"
    "${CMAKE_CURRENT_BINARY_DIR}/defaults.h"
    )
