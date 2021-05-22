#include "kruskal.h"
#include "maze.h"


auto main() -> int
{
    constexpr std::size_t maze_dimension { 30 };

    graphs::maze m { maze_dimension, [](graphs::graph<std::size_t> g){return graphs::kruskal(std::move(g), false);}};

    m.show();
}
