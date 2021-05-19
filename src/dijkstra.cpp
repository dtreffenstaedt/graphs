#include "dijkstra.h"

#include <iostream>

auto main() -> int
{
    constexpr std::size_t n { 7 };

    graphs::graph<n, std::size_t> graph { std::array<std::array<std::size_t, n>, n>{{
        { 0, 0, 0, 8, 0, 0, 10 },
        { 0, 0, 2, 0, 6, 0, 9 },
        { 0, 2, 0, 2, 3, 0, 0 },
        { 8, 0, 2, 0, 0, 8, 0 },
        { 0, 6, 3, 0, 0, 1, 0 },
        { 0, 0, 0, 8, 1, 0, 0 },
        { 10, 9, 0, 0, 0, 0, 0 }
      }}};

    std::array<std::string, n> names { "a", "b", "c", "d", "e", "f", "s" };

    std::cout << graph
            <<"\nDijkstra (start = "<<names[6]<<"): \n\n"
            << dijkstra(graph, 6);

}
