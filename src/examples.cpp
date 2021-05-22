#include "kruskal.h"
#include "prim.h"
#include "dijkstra.h"
#include "dfs.h"
#include "bfs.h"

#include <iostream>

auto main() -> int
{


/*
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
    graphs::graph<n, std::size_t> graph { std::array<std::array<std::size_t, n>, n> { {
        { 0, 0, 0, 8, 0, 0, 10 },
        { 0, 0, 2, 0, 6, 0, 9 },
        { 0, 2, 0, 2, 3, 0, 0 },
        { 8, 0, 2, 0, 0, 8, 0 },
        { 0, 6, 3, 0, 0, 1, 0 },
        { 0, 0, 0, 8, 1, 0, 0 },
        { 10, 9, 0, 0, 0, 0, 0 },
    } } };
    */
    constexpr std::size_t n { 20 };
    graphs::graph<n, std::size_t> graph { std::array<std::array<std::size_t, n>, n> { {
        {27 ,22 , 4 ,26 ,23 ,22 ,43 ,10 ,15 ,28 ,26 ,36 ,29 ,19 ,50 ,34 ,30 , 2 ,35 ,19},
        {22 ,42 , 7 , 4 ,14 , 6 ,36 ,27 ,14 ,34 ,46 ,11 , 9 ,12 , 4 ,34 ,50 ,27 ,43 ,29},
        { 4 , 7 , 4 ,41 ,27 ,39 ,28 ,31 ,18 ,24 ,32 ,10 ,37 ,49 ,45 ,20 ,39 ,15 ,40 ,36},
        {26 , 4 ,41 ,50 ,46 ,50 ,26 , 5 ,42 , 1 , 1 ,31 ,26 ,22 ,13 ,36 ,42 ,45 ,40 ,25},
        {23 ,14 ,27 ,46 ,11 , 1 ,41 ,33 ,19 , 9 ,30 ,44 ,15 ,42 ,39 ,35 ,47 ,33 ,20 ,22},
        {22 , 6 ,39 ,50 , 1 ,28 ,27 , 4 , 5 ,17 ,48 ,26 ,38 , 0 ,28 ,39 , 0 ,29 , 0 ,36},
        {43 ,36 ,28 ,26 ,41 ,27 ,22 ,15 ,40 ,29 ,43 ,45 ,27 ,31 ,35 , 4 ,33 ,27 , 1 ,29},
        {10 ,27 ,31 , 5 ,33 , 4 ,15 ,22 ,16 ,42 ,14 ,38 ,11 ,36 ,34 , 1 ,16 ,46 ,17 , 1},
        {15 ,14 ,18 ,42 ,19 , 5 ,40 ,16 , 0 ,18 ,34 ,31 ,37 , 0 ,32 ,18 ,31 ,11 ,21 ,47},
        {28 ,34 ,24 , 1 , 9 ,17 ,29 ,42 ,18 ,36 ,47 ,35 ,35 ,33 ,23 ,48 ,38 ,50 ,44 ,48},
        {26 ,46 ,32 , 1 ,30 ,48 ,43 ,14 ,34 ,47 ,32 ,13 , 0 ,30 ,38 ,49 ,21 ,28 ,46 ,40},
        {36 ,11 ,10 ,31 ,44 ,26 ,45 ,38 ,31 ,35 ,13 , 1 ,11 ,38 ,24 ,25 ,25 ,22 , 4 ,22},
        {29 , 9 ,37 ,26 ,15 ,38 ,27 ,11 ,37 ,35 , 0 ,11 ,30 , 2 ,13 ,21 ,30 ,30 ,17 , 0},
        {19 ,12 ,49 ,22 ,42 , 0 ,31 ,36 , 0 ,33 ,30 ,38 , 2 ,39 ,25 ,20 ,33 , 1 ,21 , 2},
        {50 , 4 ,45 ,13 ,39 ,28 ,35 ,34 ,32 ,23 ,38 ,24 ,13 ,25 ,40 ,49 ,10 , 8 ,26 ,37},
        {34 ,34 ,20 ,36 ,35 ,39 , 4 , 1 ,18 ,48 ,49 ,25 ,21 ,20 ,49 , 2 ,38 ,30 , 0 ,23},
        {30 ,50 ,39 ,42 ,47 , 0 ,33 ,16 ,31 ,38 ,21 ,25 ,30 ,33 ,10 ,38 , 5 ,45 ,42 ,25},
        { 2 ,27 ,15 ,45 ,33 ,29 ,27 ,46 ,11 ,50 ,28 ,22 ,30 , 1 , 8 ,30 ,45 ,19 ,12 ,40},
        {35 ,43 ,40 ,40 ,20 , 0 , 1 ,17 ,21 ,44 ,46 , 4 ,17 ,21 ,26 , 0 ,42 ,12 , 0 , 9},
        {19 ,29 ,36 ,25 ,22 ,36 ,29 , 1 ,47 ,48 ,40 ,22 , 0 , 2 ,37 ,23 ,25 ,40 , 9 ,24}
    } } };

    std::cout<<graph<<'\n';

    std::cout <<"\nDFS start = 6\n";
    graphs::dfs(graph, 6, true);
    std::cout <<"\nBFS start = 6\n";
    graphs::bfs(graph, 6, true);
    std::cout <<"\nDijkstra start = 6\n";
    graphs::dijkstra(graph, 6, true);
    std::cout <<"\nPrim start = 6\n";
    graphs::prim(graph, 6, true);
    std::cout <<"\nKruskal\n";
    graphs::kruskal(graph, true);
}
