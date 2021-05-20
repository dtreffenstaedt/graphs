#ifndef GRAPHS_KRUSKAL_H
#define GRAPHS_KRUSKAL_H

#include "graph.h"

#include <algorithm>
#include <limits>
#include <numeric>
#include <stack>

namespace graphs {

template <std::size_t N, typename W>
[[nodiscard]] auto kruskal(graph<N, W> g) -> graph<N, W>
{
    struct edge_t {
        std::size_t first {};
        std::size_t second {};
        W weight {};
    };

    std::vector<edge_t> edges {};
    for (std::size_t i { 0 }; i < (N - 1); i++) {
        for (std::size_t j { i + 1 }; j < N; j++) {
            if (g.weight(i, j) != 0) {
                edges.emplace_back(edge_t { i, j, g.weight(i, j) });
            }
        }
    }

    std::sort(edges.begin(), edges.end(), [&](const edge_t& lhs, const edge_t& rhs) { return lhs.weight < rhs.weight; });

    graph<N, W> result {};

    for (edge_t k { edges.front() }; !edges.empty();) {
        if (!result.connected(k.first, k.second)) {
            result.set(k.first, k.second, k.weight);
        }

        edges.erase(edges.begin());
        k = edges.front();
    }

    return result;
}

} // namespace graphs

#endif // GRAPHS_KRUSKAL_H
