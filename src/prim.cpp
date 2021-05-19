#include "graph.h"

#include <limits>
#include <numeric>

#include <algorithm>

#include <iostream>

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

auto main() -> int
{

    constexpr std::size_t n { 7 };

    std::array<std::string, n> names { "1", "2", "3", "4", "5", "6", "7" };

    graphs::graph<n, std::size_t> graph { std::array<std::array<std::size_t, n>, n> { {
        { 0, 14, 0, 10, 0, 0, 0 },
        { 14, 0, 16, 18, 13, 0, 0 },
        { 0, 16, 0, 0, 9, 0, 0 },
        { 10, 18, 0, 0, 30, 17, 12 },
        { 0, 13, 9, 30, 0, 0, 16 },
        { 0, 0, 0, 17, 0, 0, 22 },
        { 0, 0, 0, 12, 16, 22, 0 },
    } } };

    graph.print(std::cout);
    std::cout<<"\nPrim (start = "<<names[0]<<"): \n";

    prim(graph, 0).print(std::cout);
}
