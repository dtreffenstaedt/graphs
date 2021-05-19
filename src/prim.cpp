#include "graph.h"

#include <limits>
#include <numeric>

#include <algorithm>

#include <iostream>

namespace graphs {

template <std::size_t N, typename W>
[[nodiscard]] auto prim(graph<N, W> g, std::size_t start) -> std::array<std::size_t, N>
{
    std::array<std::size_t, N> parents {}; // The parent nodes to all nodes

    parents.at(start) = start;

    std::vector<std::size_t> unvisited {};
    for (std::size_t i { 0 }; i < N; i++) {
        unvisited.emplace_back(i);
    }

    std::vector<std::size_t> visited {};

    std::size_t i { start };
    while (visited.size() < N) {
        unvisited.erase(std::find(unvisited.begin(), unvisited.end(), i));
        visited.emplace_back(i);

        std::size_t min_i { 0 };
        std::size_t min_j { 0 };
        W min { std::numeric_limits<W>::max() };

        for (std::size_t j_i { 0 }; j_i < unvisited.size(); j_i++) {
            const std::size_t j { unvisited.at(j_i) };

            for (std::size_t k_i { 0 }; k_i < visited.size(); k_i++) {
                const std::size_t k { visited.at(k_i) };
                W weight { g.get(k, j) };
                if (weight == 0) {
                    continue;
                }
                if (weight < min) {
                    min_i = j;
                    min_j = k;
                    min = weight;
                }
            }
        }

        parents.at(min_i) = min_j;
        i = min_i;
    }

    return parents;
}


} // namespace graphs

auto main() -> int {

    graphs::graph<7, std::size_t> graph{std::array<std::size_t, 7*7>{
            0, 14, 0, 10, 0, 0, 0,
            14, 0, 16, 18, 13, 0, 0,
            0, 16, 0, 0, 9, 0, 0,
            10, 18, 0, 0, 30, 17, 12,
            0, 13, 9, 30, 0, 0, 16,
            0, 0, 0, 17, 0, 0, 22,
            0, 0, 0, 12, 16, 22, 0,
        }};

    auto parents = prim(graph, 0);

    for (std::size_t i { 0 }; i < 7; i++) {
        std::cout<<std::to_string(i);
        for (std::size_t j { parents.at(i) };;) {
            std::cout<<" <- "<<std::to_string(j);
            if (j == parents.at(j)) {
                break;
            }
            j = parents.at(j);
        }
        std::cout<<"\n";
    }
}
