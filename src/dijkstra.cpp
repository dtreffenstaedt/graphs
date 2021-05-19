#include "graph.h"

#include <limits>
#include <numeric>

#include <iostream>

namespace graphs {

template <std::size_t N, typename W>
[[nodiscard]] auto dijkstra(graph<N, W> g, std::size_t start) -> std::array<std::size_t, N>
{
    std::array<W, N> weights {}; // Stores the current total weights of the nodes
    std::array<std::size_t, N> parents {}; // The parent nodes to all nodes
    std::array<bool, N> visited {}; // store the visited nodes

    visited.fill(false);
    weights.fill(std::numeric_limits<W>::max());
    weights.at(start) = 0; // set the weigth of the starting node to 0

    parents.at(start) = start; // set the parent of the start node to itself

    std::size_t n_visited { 1 }; // number of visited nodes

    for (std::size_t i { start };;) {

        visited.at(i) = true; // set the current node to visited

        n_visited++;
        // go through all nodes
        for (std::size_t j { 0 }; j < N; j++) {

            W weight = g.weight(i, j); // get the weight of the current node

            // if the node is already visited or not connected to the current node, skip it
            if ((weight == 0) || (visited.at(j))) {
                continue;
            }

            // if the weight decreases by going through the current node, update the tree
            if (weights.at(j) > (weights.at(i) + weight)) {
                weights.at(j) = weights.at(i) + weight;
                parents.at(j) = i;
            }
        }

        std::size_t min_i { 0 };
        W min { std::numeric_limits<W>::max() };

        // find the next node to visit
        for (std::size_t k { 0 }; k < N; k++) {
            if (visited.at(k)) {
                continue;
            }
            if (weights.at(k) < min) {
                min_i = k;
                min = weights.at(k);
            }
        }
        // cancel criterium
        if (n_visited == N) {
            break;
        }
        i = min_i;
    }

    return parents;
}

} // namespace graphs

auto main() -> int {

    constexpr std::size_t n { 7 };

    std::array<std::string, n> names {"a", "b", "c", "d", "e", "f", "s"};

    graphs::graph<n, std::size_t> graph{std::array<std::size_t, n*n>{
             0, 0, 0, 8, 0, 0, 10
            ,0, 0, 2, 0, 6, 0, 9
            ,0, 2, 0, 2, 3, 0, 0
            ,8, 0, 2, 0, 0, 8, 0
            ,0, 6, 3, 0, 0, 1, 0
            ,0, 0, 0, 8, 1, 0, 0
            ,10, 9, 0, 0, 0, 0, 0
        }};
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
