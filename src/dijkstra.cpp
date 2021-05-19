#include "graph.h"

#include <algorithm>
#include <limits>
#include <numeric>

#include <iostream>

namespace graphs {

template <std::size_t N, typename W>
[[nodiscard]] auto dijkstra(graph<N, W> g, std::size_t start) -> std::array<std::size_t, N>
{
    std::array<W, N> weights {}; // Stores the current total weights of the nodes
    std::array<std::size_t, N> parents {}; // The parent nodes to all nodes

    std::vector<std::size_t> unvisited {};
    unvisited.resize(N);

    std::iota(unvisited.begin(), unvisited.end(), 0);

    std::fill(weights.begin(), weights.end(), std::numeric_limits<W>::max());
    weights.at(start) = 0; // set the weigth of the starting node to 0

    parents.at(start) = start; // set the parent of the start node to itself

    for (std::size_t i { start }; !unvisited.empty();) {
        unvisited.erase(std::find(unvisited.begin(), unvisited.end(), i));

        std::size_t min_i { 0 };

        W min { std::numeric_limits<W>::max() };

        for (const auto& j : unvisited) {
            W weight = g.weight(i, j); // get the weight of the current node

            // if the node is not connected to the current node, skip it
            if (weight != 0) {
                // if the weight decreases by going through the current node, update the tree
                if (weights.at(j) > (weights.at(i) + weight)) {
                    weights.at(j) = weights.at(i) + weight;
                    parents.at(j) = i;
                }
            }
            if (weights.at(j) < min) {
                min_i = j;
                min = weights.at(j);
            }
        }

        i = min_i;
    }

    return parents;
}

} // namespace graphs

auto main() -> int
{

    constexpr std::size_t n { 7 };

    std::array<std::string, n> names { "a", "b", "c", "d", "e", "f", "s" };

    graphs::graph<n, std::size_t> graph { std::array<std::array<std::size_t, n>, n>{{
                { 0, 0, 0, 8, 0, 0, 10 },
                { 0, 0, 2, 0, 6, 0, 9 },
                { 0, 2, 0, 2, 3, 0, 0 },
                { 8, 0, 2, 0, 0, 8, 0 },
                { 0, 6, 3, 0, 0, 1, 0 },
                { 0, 0, 0, 8, 1, 0, 0 },
                { 10, 9, 0, 0, 0, 0, 0 }
              }}};
    auto parents = dijkstra(graph, 6);

    for (std::size_t i { 0 }; i < n; i++) {
        std::cout << names.at(i);
        for (std::size_t j { parents.at(i) };;) {
            std::cout << " <- " << names.at(j);
            if (j == parents.at(j)) {
                break;
            }
            j = parents.at(j);
        }
        std::cout << "\n";
    }
}
