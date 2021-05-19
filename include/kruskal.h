#ifndef GRAPHS_KRUSKAL_H
#define GRAPHS_KRUSKAL_H


#include "graph.h"

#include <limits>
#include <numeric>
#include <stack>
#include <algorithm>


namespace graphs {


template <std::size_t N, typename W>
[[nodiscard]] auto kruskal(graph<N, W> g) -> graph<N, W>
{
    auto connected {[] (graph<N, W> g, std::size_t start, std::size_t search) -> bool {
            std::stack<std::size_t> stack {};
            stack.push(start);

            std::vector<std::size_t> unvisited {};
            unvisited.resize(N);
            std::iota(unvisited.begin(), unvisited.end(), 0);

            for (std::size_t i { stack.top() }; !stack.empty();) {
                unvisited.erase(std::find(unvisited.begin(), unvisited.end(), i));
                stack.pop();
                if (i == search) {
                    return true;
                }

                for (const auto& j : unvisited) {
                    if (g.weight(i, j) != 0) {
                        stack.push(j);
                    }
                }
                i = stack.top();
            }
            return false;
        }};

    struct edge_t {
        std::size_t first {};
        std::size_t second {};
        W weight {};
    };

    std::vector<edge_t> edges {};
    for (std::size_t i { 0 }; i < (N - 1); i++) {
        for (std::size_t j { i + 1 }; j < N; j++) {
            if (g.weight(i, j) != 0) {
                edges.emplace_back(edge_t{i, j, g.weight(i, j)});
            }
        }
    }

    std::sort(edges.begin(), edges.end(), [&](const edge_t& lhs, const edge_t& rhs){return lhs.weight < rhs.weight;});

    graph<N, W> result{};

    for (edge_t k { edges.front() }; !edges.empty();) {
        if (!connected(result, k.first, k.second)) {
            result.set(k.first, k.second, k.weight);
        }

        edges.erase(edges.begin());
        k = edges.front();
    }

    return result;
}

} // namespace graphs

#endif // GRAPHS_KRUSKAL_H
