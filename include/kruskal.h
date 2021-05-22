#ifndef GRAPHS_KRUSKAL_H
#define GRAPHS_KRUSKAL_H

#include "graph.h"

#include <algorithm>
#include <limits>
#include <numeric>
#include <stack>

#include <thread>
#include <iostream>

namespace graphs {

template <typename W>
auto kruskal(graph<W> g, bool print = false) -> graph<W>
{
    struct edge_t {
        std::size_t first {};
        std::size_t second {};
        W weight {};
    };

    std::vector<edge_t> edges {};
    for (std::size_t i { 0 }; i < (g.dimension() - 1); i++) {
        for (std::size_t j { i + 1 }; j < g.dimension(); j++) {
            if (g.weight(i, j) != 0) {
                edges.emplace_back(edge_t { i, j, g.weight(i, j) });
            }
        }
    }

    std::sort(edges.begin(), edges.end(), [&](const edge_t& lhs, const edge_t& rhs) { return lhs.weight < rhs.weight; });

    graph<W> result {g.dimension()};

    if (print) {
        std::cout<<result;
    }

    for (const auto& edge : edges) {
        if (!result.connected_bi_bfs(edge.first, edge.second)) {
            result.set(edge.first, edge.second, edge.weight);

        if (print) {
                std::this_thread::sleep_for(std::chrono::milliseconds{300});
                std::cout<<"\033["<<std::to_string(g.dimension())<<"A\r"<<result;
                std::this_thread::sleep_for(std::chrono::milliseconds{300});
        }
        }
    }

    if (print) {
        std::cout<<'\n';
    }

    return result;
}

} // namespace graphs

#endif // GRAPHS_KRUSKAL_H
