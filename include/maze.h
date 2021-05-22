#ifndef MAZE_H
#define MAZE_H

#include "graph.h"


#include <random>
#include <algorithm>
#include <iostream>
#include <thread>

namespace graphs {
class maze {
public:
    maze(std::size_t dimension);

    void show();

    [[nodiscard]] auto graph() const -> graphs::graph<bool>;

private:
    void show(std::size_t first, std::size_t second);
    void generate();
    void generate_graph();
    void generate_maze();
    [[nodiscard]] auto pos(std::size_t x, std::size_t y) const -> std::size_t;

    std::size_t m_dimension;
    graphs::graph<bool> m_graph;
};

maze::maze(std::size_t dimension)
    : m_dimension { dimension }
    , m_graph { dimension * dimension }
{
    generate();
}

auto maze::pos(std::size_t x, std::size_t y) const -> std::size_t
{
    return m_dimension*x + y;
}

void maze::generate()
{
    generate_graph();
    generate_maze();
}

void maze::generate_graph()
{
    for (std::size_t x { 0 }; x < m_dimension; x++) {
        for (std::size_t y { 0 }; y < m_dimension; y++) {
            if (x != (m_dimension - 1)) {
                m_graph.set(pos(x, y), pos(x + 1,y));
            }
            if (y != (m_dimension - 1)) {
                m_graph.set(pos(x, y), pos(x,y + 1));
            }
        }
    }
}

void maze::generate_maze()
{
    struct edge_t {
        std::size_t first {};
        std::size_t second {};
    };

    std::vector<edge_t> edges {};
    for (std::size_t i { 0 }; i < (m_graph.dimension() - 1); i++) {
        for (std::size_t j { i + 1 }; j < m_graph.dimension(); j++) {
            if (m_graph.weight(i, j) != 0) {
                edges.emplace_back(edge_t { i, j });
            }
        }
    }

    std::random_device rd;
    std::mt19937 g(rd());

    std::cout<<"Shuffling edges... ";
    std::shuffle(edges.begin(), edges.end(), g);
    std::cout<<"shuffled\nRearranging edges...\n";

    std::size_t i { 0 };
    for (const auto& edge : edges) {
        m_graph.unset(edge.first, edge.second);
        if (!m_graph.connected_bi_bfs(edge.first, edge.second)) {
            m_graph.set(edge.first, edge.second);
        }
        std::ostringstream out{};
        out<<std::setfill(' ')<<std::setw(7)<<i<<'/'<<std::setw(7)<<edges.size();
        std::cout<<'\r'<<out.str();
        i++;
    }

    std::cout<<'\n';
    show();
}

void maze::show(std::size_t first, std::size_t second)
{
    for (std::size_t y { 0 }; y < m_dimension; y++) {
        for (std::size_t x { 0 }; x < m_dimension; x++) {
            if (x < (m_dimension - 1)) {
                const std::size_t a { pos(x,y)};
                const std::size_t b { pos(x+1,y)};
                if (m_graph.weight(a, b)) {
                    if (((a == first) && (b == second)) || ((b == first) && (a == second))) {
                        std::cout<<"·\033[1;31m-\033[0m";
                    } else {
                        std::cout<<"·-";
                    }
                } else {
                    std::cout<<"· ";
                }
            } else {
                std::cout<<"·";
            }
        }
        std::cout<<'\n';
        for (std::size_t x { 0 }; x < m_dimension; x++) {
            if (y < (m_dimension - 1)) {
                const std::size_t a { pos(x,y)};
                const std::size_t b { pos(x,y+1)};
                if (m_graph.weight(a, b)) {
                    if (((a == first) && (b == second)) || ((b == first) && (a == second))) {
                        std::cout<<"\033[1;31m|\033[0m ";
                    } else {
                        std::cout<<"| ";
                    }
                } else {
                    std::cout<<"  ";
                }
            }
        }
        std::cout<<'\n';
    }
}

void maze::show()
{
    for (std::size_t y { 0 }; y < m_dimension; y++) {
        for (std::size_t x { 0 }; x < m_dimension; x++) {
            if (x < (m_dimension - 1)) {
                if (m_graph.weight(pos(x,y), pos(x+1,y))) {
                    std::cout<<"·-";
                } else {
                    std::cout<<"· ";
                }
            } else {
                std::cout<<"·";
            }
        }
        std::cout<<'\n';
        for (std::size_t x { 0 }; x < m_dimension; x++) {
            if (y < (m_dimension - 1)) {
                if (m_graph.weight(pos(x,y), pos(x,y+1))) {
                    std::cout<<"| ";
                } else {
                    std::cout<<"  ";
                }
            }
        }
        std::cout<<'\n';
    }
}

auto maze::graph() const -> graphs::graph<bool>
{
    return m_graph;
}
}

#endif // MAZE_H
