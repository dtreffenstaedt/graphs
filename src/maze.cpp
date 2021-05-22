#include "kruskal.h"

#include <iostream>

#include <random>

template <std::size_t N>
auto generate_grid_graph() -> graphs::graph<N*N, std::size_t>
{
    auto pos {[](std::size_t x, std::size_t y)->std::size_t {
            return N*x + y;
        }};

    graphs::graph<N*N, std::size_t> result {};

    std::random_device rd;
    std::uniform_int_distribution<std::size_t> dist(0, 99);
    for (std::size_t x { 0 }; x < N; x++) {
        for (std::size_t y { 0 }; y < N; y++) {
            if (x != (N - 1)) {
                result.set(pos(x, y), pos(x + 1,y), dist(rd));
            }
            if (y != (N - 1)) {
                result.set(pos(x, y), pos(x,y + 1), dist(rd));
            }
        }
    }

    return result;
}

template <std::size_t N>
void show_labyrinth(graphs::graph<N*N> graph = graphs::kruskal(generate_grid_graph<N>(), false).remove_weight())
{
    auto pos {[](std::size_t x, std::size_t y)->std::size_t {
            return N*x + y;
        }};

    for (std::size_t y { 0 }; y < N; y++) {
        for (std::size_t x { 0 }; x < N; x++) {
            if (x < (N - 1)) {
                if (graph.weight(pos(x,y), pos(x+1,y))) {
                    std::cout<<"·-";
                } else {
                    std::cout<<"· ";
                }
            }
        }
        std::cout<<'\n';
        for (std::size_t x { 0 }; x < N; x++) {
            if (y < (N - 1)) {
                if (graph.weight(pos(x,y), pos(x,y+1))) {
                    std::cout<<"| ";
                } else {
                    std::cout<<"  ";
                }
            }
        }
        std::cout<<'\n';
    }
}

auto main() -> int
{

    show_labyrinth<50>();
}
