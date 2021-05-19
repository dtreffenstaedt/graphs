#include "prim.h"

#include <iostream>

auto main() -> int
{
    constexpr std::size_t n { 7 };

    graphs::graph<n, std::size_t> graph { std::array<std::array<std::size_t, n>, n> { {
        { 0, 14, 0, 10, 0, 0, 0 },
        { 14, 0, 16, 18, 13, 0, 0 },
        { 0, 16, 0, 0, 9, 0, 0 },
        { 10, 18, 0, 0, 30, 17, 12 },
        { 0, 13, 9, 30, 0, 0, 16 },
        { 0, 0, 0, 17, 0, 0, 22 },
        { 0, 0, 0, 12, 16, 22, 0 },
    } } };

    std::array<std::string, n> names { "1", "2", "3", "4", "5", "6", "7" };

    std::cout << graph
              << "\nPrim (start = " << names[0] << "): \n\n"
              << prim(graph, 0);
}
