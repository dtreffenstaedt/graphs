#ifndef GRAPHS_DFS_H
#define GRAPHS_DFS_H

#include "graph.h"

#include <algorithm>
#include <limits>
#include <numeric>
#include <stack>

namespace graphs {

template <std::size_t N, typename W>
[[nodiscard]] auto dfs(graph<N, W> g, std::size_t start) -> graph<N, W>
{
    std::stack<std::size_t> stack {};
    stack.emplace(start);

    std::vector<std::size_t> unvisited {};
    unvisited.resize(N);
    std::iota(unvisited.begin(), unvisited.end(), 0);

    graph<N, W> result {};

    std::size_t last { stack.top() };
    unvisited.erase(std::find(unvisited.begin(), unvisited.end(), stack.top()));
    for (std::size_t i { stack.top() }; !stack.empty();) {
        stack.pop();
        result.set(last, i, g.weight(last, i));

        for (const auto& j : unvisited) {
            if (g.weight(i, j) != 0) {
                unvisited.erase(std::find(unvisited.begin(), unvisited.end(), j));
                stack.emplace(j);
            }
        }
        last = i;
        i = stack.top();
    }

    return result;
}

} // namespace graphs

#endif // GRAPHS_DFS_H
