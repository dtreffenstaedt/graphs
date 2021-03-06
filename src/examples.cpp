#include "bfs.h"
#include "dfs.h"
#include "dijkstra.h"
#include "kruskal.h"
#include "prim.h"

#include <boost/program_options.hpp>
#include <iostream>

auto main(int argc, const char* argv[]) -> int
{
    namespace po = boost::program_options;
    po::variables_map options {};

    po::options_description desc("General options");
    desc.add_options()("help,h", "produce help message")
            ("first", "Show the prim algorithm from the task sheet")
            ("third", "Show the dijkstra algorithm from the task sheet")
            ("prim", po::value<std::size_t>(), "Show the prim algorithm")
            ("dijkstra", po::value<std::size_t>(), "Show the dijkstra algorithm")
            ("kruskal", "Show the kruksal algorithm")
            ("bfs", po::value<std::size_t>(), "Show the bfs algorithm")
            ("dfs", po::value<std::size_t>(), "Show the dfs algorithm")
            ("no-colour,n", "do not print using colour")
            ;

    po::store(po::parse_command_line(argc, argv, desc), options);
    if ((options.count("help") != 0) || options.empty()) {
        std::cout << desc;
        return 0;
    }
    po::notify(options);
    bool colour { options.count("no-colour") == 0 };

    if (options.count("third") != 0) {
        graphs::graph<std::size_t> graph { { {
            { 0, 14, 0, 10, 0, 0, 0 },
            { 14, 0, 16, 18, 13, 0, 0 },
            { 0, 16, 0, 0, 9, 0, 0 },
            { 10, 18, 0, 0, 30, 17, 12 },
            { 0, 13, 9, 30, 0, 0, 16 },
            { 0, 0, 0, 17, 0, 0, 22 },
            { 0, 0, 0, 12, 16, 22, 0 },
        } }, colour };
        graphs::prim(graph, 0, true);
    }

    if (options.count("first") != 0) {
        graphs::graph<std::size_t> graph { { {
            { 0, 0, 0, 8, 0, 0, 10 },
            { 0, 0, 2, 0, 6, 0, 9 },
            { 0, 2, 0, 2, 3, 0, 0 },
            { 8, 0, 2, 0, 0, 8, 0 },
            { 0, 6, 3, 0, 0, 1, 0 },
            { 0, 0, 0, 8, 1, 0, 0 },
            { 10, 9, 0, 0, 0, 0, 0 },
        } } , colour};
        graphs::dijkstra(graph, 6, true);
    }

    graphs::graph<std::size_t> graph { { {
        { 0, 19, 27, 33, 11, 30, 48, 27, 39, 8, 11, 7, 21, 6, 43, 14, 21, 16, 31, 41, 7, 24, 3, 5, 12, 10, 45, 7, 10, 34 },
        { 19, 0, 30, 10, 43, 10, 39, 32, 1, 49, 1, 27, 41, 7, 43, 20, 25, 6, 10, 2, 23, 20, 31, 41, 2, 6, 19, 40, 39, 36 },
        { 27, 30, 0, 36, 38, 9, 9, 2, 24, 21, 37, 12, 20, 9, 19, 25, 2, 23, 24, 29, 27, 32, 6, 17, 2, 35, 23, 50, 18, 21 },
        { 33, 10, 36, 0, 15, 13, 19, 40, 10, 5, 41, 32, 20, 10, 6, 31, 25, 25, 10, 15, 30, 1, 32, 45, 48, 47, 21, 29, 5, 33 },
        { 11, 43, 38, 15, 0, 32, 31, 36, 7, 46, 36, 50, 1, 8, 15, 22, 8, 0, 33, 3, 0, 4, 0, 40, 46, 41, 22, 22, 49, 1 },
        { 30, 10, 9, 13, 32, 0, 16, 50, 15, 14, 11, 39, 0, 13, 28, 31, 1, 36, 9, 23, 31, 21, 14, 50, 38, 13, 30, 15, 36, 12 },
        { 48, 39, 9, 19, 31, 16, 0, 39, 23, 50, 24, 4, 19, 34, 42, 25, 41, 0, 28, 23, 15, 16, 22, 42, 9, 6, 34, 38, 44, 9 },
        { 27, 32, 2, 40, 36, 50, 39, 0, 8, 12, 27, 17, 27, 18, 4, 1, 16, 10, 44, 43, 24, 34, 43, 34, 27, 33, 20, 25, 39, 27 },
        { 39, 1, 24, 10, 7, 15, 23, 8, 0, 34, 32, 37, 11, 41, 50, 7, 26, 18, 38, 33, 10, 13, 32, 41, 24, 34, 15, 28, 23, 41 },
        { 8, 49, 21, 5, 46, 14, 50, 12, 34, 0, 0, 39, 28, 7, 21, 37, 13, 43, 42, 38, 36, 34, 35, 12, 7, 21, 32, 8, 20, 9 },
        { 11, 1, 37, 41, 36, 11, 24, 27, 32, 0, 0, 39, 13, 42, 31, 23, 21, 21, 39, 16, 8, 28, 44, 34, 18, 29, 20, 40, 30, 4 },
        { 7, 27, 12, 32, 50, 39, 4, 17, 37, 39, 39, 0, 25, 14, 39, 49, 29, 15, 35, 31, 49, 50, 30, 14, 39, 9, 0, 38, 49, 24 },
        { 21, 41, 20, 20, 1, 0, 19, 27, 11, 28, 13, 25, 0, 48, 13, 26, 45, 37, 32, 48, 50, 11, 48, 15, 45, 5, 18, 23, 17, 39 },
        { 6, 7, 9, 10, 8, 13, 34, 18, 41, 7, 42, 14, 48, 0, 46, 35, 41, 19, 50, 25, 48, 50, 41, 29, 14, 17, 39, 15, 20, 30 },
        { 43, 43, 19, 6, 15, 28, 42, 4, 50, 21, 31, 39, 13, 46, 0, 49, 18, 21, 20, 13, 4, 5, 36, 49, 29, 9, 41, 12, 3, 6 },
        { 14, 20, 25, 31, 22, 31, 25, 1, 7, 37, 23, 49, 26, 35, 49, 0, 36, 47, 34, 33, 25, 29, 18, 26, 31, 23, 14, 5, 16, 12 },
        { 21, 25, 2, 25, 8, 1, 41, 16, 26, 13, 21, 29, 45, 41, 18, 36, 0, 43, 13, 5, 23, 1, 39, 15, 9, 4, 37, 31, 4, 39 },
        { 16, 6, 23, 25, 0, 36, 0, 10, 18, 43, 21, 15, 37, 19, 21, 47, 43, 0, 6, 33, 35, 3, 17, 36, 48, 39, 43, 39, 25, 46 },
        { 31, 10, 24, 10, 33, 9, 28, 44, 38, 42, 39, 35, 32, 50, 20, 34, 13, 6, 0, 3, 10, 23, 2, 35, 22, 4, 9, 34, 15, 21 },
        { 41, 2, 29, 15, 3, 23, 23, 43, 33, 38, 16, 31, 48, 25, 13, 33, 5, 33, 3, 0, 43, 45, 32, 45, 27, 46, 32, 12, 30, 15 },
        { 7, 23, 27, 30, 0, 31, 15, 24, 10, 36, 8, 49, 50, 48, 4, 25, 23, 35, 10, 43, 0, 50, 19, 14, 42, 37, 45, 19, 9, 50 },
        { 24, 20, 32, 1, 4, 21, 16, 34, 13, 34, 28, 50, 11, 50, 5, 29, 1, 3, 23, 45, 50, 0, 2, 19, 13, 22, 31, 35, 14, 44 },
        { 3, 31, 6, 32, 0, 14, 22, 43, 32, 35, 44, 30, 48, 41, 36, 18, 39, 17, 2, 32, 19, 2, 0, 9, 27, 9, 33, 44, 41, 50 },
        { 5, 41, 17, 45, 40, 50, 42, 34, 41, 12, 34, 14, 15, 29, 49, 26, 15, 36, 35, 45, 14, 19, 9, 0, 35, 24, 11, 12, 13, 5 },
        { 12, 2, 2, 48, 46, 38, 9, 27, 24, 7, 18, 39, 45, 14, 29, 31, 9, 48, 22, 27, 42, 13, 27, 35, 0, 46, 38, 18, 23, 21 },
        { 10, 6, 35, 47, 41, 13, 6, 33, 34, 21, 29, 9, 5, 17, 9, 23, 4, 39, 4, 46, 37, 22, 9, 24, 46, 0, 34, 16, 20, 14 },
        { 45, 19, 23, 21, 22, 30, 34, 20, 15, 32, 20, 0, 18, 39, 41, 14, 37, 43, 9, 32, 45, 31, 33, 11, 38, 34, 0, 28, 8, 25 },
        { 7, 40, 50, 29, 22, 15, 38, 25, 28, 8, 40, 38, 23, 15, 12, 5, 31, 39, 34, 12, 19, 35, 44, 12, 18, 16, 28, 0, 40, 0 },
        { 10, 39, 18, 5, 49, 36, 44, 39, 23, 20, 30, 49, 17, 20, 3, 16, 4, 25, 15, 30, 9, 14, 41, 13, 23, 20, 8, 40, 0, 17 },
        { 34, 36, 21, 33, 1, 12, 9, 27, 41, 9, 4, 24, 39, 30, 6, 12, 39, 46, 21, 15, 50, 44, 50, 5, 21, 14, 25, 0, 17, 0 } } } , colour};

    if (options.count("prim") != 0) {
        graphs::prim(graph, options["prim"].as<std::size_t>(), true);
    } else if (options.count("dijkstra") != 0) {
        graphs::dijkstra(graph, options["dijkstra"].as<std::size_t>(), true);
    } else if (options.count("kruskal") != 0) {
        graphs::kruskal(graph, true);
    } else if (options.count("bfs") != 0) {
        graphs::bfs(graph, options["bfs"].as<std::size_t>(), true);
    } else if (options.count("dfs") != 0) {
        graphs::dfs(graph, options["dfs"].as<std::size_t>(), true);
    }
}
