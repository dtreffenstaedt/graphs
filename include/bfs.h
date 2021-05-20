#ifndef GRAPHS_BFS_H
#define GRAPHS_BFS_H

#include "graph.h"

#include <algorithm>
#include <limits>
#include <numeric>
#include <queue>

namespace graphs {

template <std::size_t N, typename W>
[[nodiscard]] auto bfs(graph<N, W> g, std::size_t start) -> graph<N, W>
{
    std::queue<std::size_t> queue {};
    queue.emplace(start);

    std::vector<std::size_t> unvisited {};
    unvisited.resize(N);
    std::iota(unvisited.begin(), unvisited.end(), 0);

    graph<N, W> result {};

    std::size_t last { queue.front() };
    unvisited.erase(std::find(unvisited.begin(), unvisited.end(), queue.front()));
    for (std::size_t i { queue.front() }; !queue.empty();) {
        queue.pop();
        result.set(last, i, g.weight(last, i));

        for (const auto& j : unvisited) {
            if (g.weight(i, j) != 0) {
                unvisited.erase(std::find(unvisited.begin(), unvisited.end(), j));
                queue.emplace(j);
            }
        }
        last = i;
        i = queue.front();
    }

    return result;
}

} // namespace graphs

#endif // GRAPHS_BFS_H
