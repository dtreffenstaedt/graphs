#ifndef GRAPHS_DFS_H
#define GRAPHS_DFS_H

#include "graph.h"

#include <algorithm>
#include <limits>
#include <numeric>
#include <stack>
#include <thread>

#include <iostream>

namespace graphs {

template <std::size_t N, typename W>
auto dfs(graph<N, W> g, std::size_t start) -> graph<N, W>
{
    struct edge_t {
        std::size_t i {};
        std::size_t parent {};
        W weight {};
    };

    std::stack<edge_t> stack {};
    stack.emplace(edge_t{start, start, 0});

    std::vector<std::size_t> unvisited {};
    unvisited.resize(N);
    std::iota(unvisited.begin(), unvisited.end(), 0);

    graph<N, W> result {};

    std::cout<<result;

    for (edge_t i { stack.top() }; !stack.empty(); i = stack.top()) {
        stack.pop();
        const auto it = std::find(unvisited.begin(), unvisited.end(), i.i);
        if (it == unvisited.end()) {
            continue;
        }
        unvisited.erase(it);

        result.set(i.parent, i.i, i.weight);

        std::this_thread::sleep_for(std::chrono::seconds{2});
        std::cout<<"\033["<<std::to_string(N)<<"A\r"<<result;

        for (const auto& j: unvisited) {
            const auto w { g.weight(i.i, j) };
            if (w == 0) {
                continue;
            }
            stack.emplace(edge_t{j, i.i, w});
        }
    }
    std::cout<<'\n';

    return result;
}

} // namespace graphs

#endif // GRAPHS_DFS_H
