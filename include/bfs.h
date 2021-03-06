#ifndef GRAPHS_BFS_H
#define GRAPHS_BFS_H

#include "graph.h"

#include <algorithm>
#include <limits>
#include <numeric>
#include <queue>

#include <iostream>
#include <thread>

namespace graphs {

template <typename W>
auto bfs(graph<W> g, std::size_t start, bool print = false) -> graph<W>
{
    struct edge_t {
        std::size_t i {};
        std::size_t parent {};
        W weight {};
    };

    std::queue<edge_t> queue {};
    queue.emplace(edge_t { start, start, 0 });

    std::vector<std::size_t> unvisited {};
    unvisited.resize(g.dimension());
    std::iota(unvisited.begin(), unvisited.end(), 0);

    graph<W> result { g.dimension(), g.colour() };

    if (print) {
        std::cout << result;
    }

    for (edge_t i { queue.front() }; !queue.empty(); i = queue.front()) {
        result.mark(i.i);
        queue.pop();
        const auto it = std::find(unvisited.begin(), unvisited.end(), i.i);
        if (it == unvisited.end()) {
            continue;
        }
        unvisited.erase(it);

        result.set(i.parent, i.i, i.weight);

        if (print) {
            std::this_thread::sleep_for(std::chrono::milliseconds { 300 });
            std::cout << "\033[" << std::to_string(g.dimension()) << "A\r" << result;
            std::this_thread::sleep_for(std::chrono::milliseconds { 300 });
        }

        for (const auto& j : unvisited) {
            const auto w { g.weight(i.i, j) };
            if (w == 0) {
                continue;
            }
            queue.emplace(edge_t { j, i.i, w });
        }
    }


    result.unmark();
    if (print) {
        std::cout << "\033[" << std::to_string(g.dimension()) << "A\r" << result;
    }
    return result;
}

} // namespace graphs

#endif // GRAPHS_BFS_H
