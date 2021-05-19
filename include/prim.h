#ifndef GRAPHS_PRIM_H
#define GRAPHS_PRIM_H

#include "graph.h"

#include <limits>
#include <numeric>
#include <algorithm>

namespace graphs {

template <std::size_t N, typename W>
[[nodiscard]] auto prim(graph<N, W> g, std::size_t start) -> graph<N, W>
{
    std::vector<std::size_t> unvisited {}; // contains all unvisited nodes
    std::vector<std::size_t> visited {}; // contains the visited nodes


    // populate the unvisited vector
    unvisited.resize(N);
    std::iota(unvisited.begin(), unvisited.end(), 0);

    graph<N, W> result {};

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
    }

    return result;
}

} // namespace graphs


#endif // GRAPHS_PRIM_H
