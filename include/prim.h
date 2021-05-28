#ifndef GRAPHS_PRIM_H
#define GRAPHS_PRIM_H

#include "graph.h"

#include <algorithm>
#include <limits>
#include <numeric>

#include <iostream>
#include <thread>

namespace graphs {

template <typename W>
auto prim(graph<W> g, std::size_t start, bool print = false) -> graph<W>
{
    std::vector<std::size_t> unvisited {}; // contains all unvisited nodes
    std::vector<std::size_t> visited {}; // contains the visited nodes

    // populate the unvisited vector
    unvisited.resize(g.dimension());
    std::iota(unvisited.begin(), unvisited.end(), 0);

    graph<W> result { g.dimension(), g.colour() };
    if (print) {
        std::cout << result;
    }

    for (std::size_t k { start }; !unvisited.empty();) {
        unvisited.erase(std::find(unvisited.begin(), unvisited.end(), k));
        visited.emplace_back(k);

        std::size_t min_i { 0 };
        std::size_t min_j { 0 };
        W min { std::numeric_limits<W>::max() };

        for (const auto& i : unvisited) {
            for (const auto& j : visited) {

                // get the weight of the edge i,j
                const W weight { g.weight(i, j) };

                // skip unconnected nodes
                if (weight == 0) {
                    continue;
                }

                // update the lowest weight node
                if (weight < min) {
                    min_i = i;
                    min_j = j;
                    min = weight;
                }
            }
        }

        k = min_i;
        result.set(min_i, min_j, g.weight(min_i, min_j));

        if (print) {
            std::this_thread::sleep_for(std::chrono::milliseconds { 300 });
            std::cout << "\033[" << std::to_string(g.dimension()) << "A\r" << result;
            std::this_thread::sleep_for(std::chrono::milliseconds { 300 });
        }
    }

    if (print) {
        std::cout << '\n';
    }

    return result;
}

} // namespace graphs

#endif // GRAPHS_PRIM_H
