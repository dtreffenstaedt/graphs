#ifndef GRAPHS_DIJKSTRA_H
#define GRAPHS_DIJKSTRA_H

#include "graph.h"

#include <algorithm>
#include <limits>
#include <numeric>

#include <thread>
#include <iostream>

namespace graphs {

template <std::size_t N, typename W>
auto dijkstra(graph<N, W> g, std::size_t start) -> graph<N, W>
{
    std::array<W, N> weights {}; // Stores the current total weights of the nodes
    std::array<std::size_t, N> parents {}; // The parent nodes to all nodes
    std::vector<std::size_t> unvisited {};
    unvisited.resize(N);

    std::iota(unvisited.begin(), unvisited.end(), 0);

    std::fill(weights.begin(), weights.end(), std::numeric_limits<W>::max());

    weights.at(start) = 0; // set the weigth of the starting node to 0

    parents.at(start) = start; // set the parent of the start node to itself

    graph<N, W> result {};

    std::cout<<result;

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

                    result.unset(parents.at(j), j);

                    result.set(j, i, weight);

                    parents.at(j) = i;

                    std::this_thread::sleep_for(std::chrono::seconds{2});
                    std::cout<<"\033["<<std::to_string(N)<<"A\r"<<result;
                }
            }
            if (weights.at(j) < min) {
                min_i = j;
                min = weights.at(j);
            }
        }

        i = min_i;
    }

    std::cout<<'\n';
    return result;
}

} // namespace graphs

#endif // GRAPHS_DIJKSTRA_H
