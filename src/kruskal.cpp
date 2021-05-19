#include "graph.h"

#include <limits>
#include <numeric>
#include <stack>

#include <algorithm>

#include <iostream>

namespace graphs {

struct edge_t {
    std::size_t first {};
    std::size_t second {};
};

template <std::size_t N, typename W>
[[nodiscard]] auto connected(graph<N, W> g, std::size_t start, std::size_t search) -> bool
{
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
}

template <std::size_t N, typename W>
[[nodiscard]] auto kruskal(graph<N, W> g) -> graph<N, W>
{
    std::vector<edge_t> edges {};
    for (std::size_t i { 0 }; i < (N - 1); i++) {
        for (std::size_t j { i + 1 }; j < N; j++) {
            if (g.weight(i, j) != 0) {
                edges.emplace_back(edge_t{i, j});
            }
        }
    }

    std::sort(edges.begin(), edges.end(), [&](const edge_t& lhs, const edge_t& rhs){return g.weight(lhs.first, lhs.second) < g.weight(rhs.first, rhs.second);});

    graph<N, W> result{};

    for (edge_t k { edges.front() }; !edges.empty();) {
        if (!connected(result, k.first, k.second)) {
            result.set(k.first, k.second, g.weight(k.first, k.second));
        }

        edges.erase(edges.begin());
        k = edges.front();
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
    std::cout<<"\nKruskal: \n";

    kruskal(graph).print(std::cout);
}
