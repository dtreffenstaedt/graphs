#ifndef MAZE_H
#define MAZE_H

#include "graph.h"


#include <random>
#include <iostream>

namespace graphs {
class maze {
public:
    maze(std::size_t dimension, std::function<graph<std::size_t>(graph<std::size_t>)> algorithm);

    void show();

    [[nodiscard]] auto graph() const -> graphs::graph<bool>;

private:
    void generate();
    [[nodiscard]] auto pos(std::size_t x, std::size_t y) const -> std::size_t;

    std::size_t m_dimension;
    std::function<graphs::graph<std::size_t>(graphs::graph<std::size_t>)> m_algorithm;
    graphs::graph<bool> m_graph;
};

maze::maze(std::size_t dimension, std::function<graphs::graph<std::size_t>(graphs::graph<std::size_t>)> algorithm)
    : m_dimension { dimension }
    , m_algorithm { std::move(algorithm) }
    , m_graph { dimension }
{
    generate();
}

auto maze::pos(std::size_t x, std::size_t y) const -> std::size_t
{
    return m_dimension*x + y;
}

void maze::generate()
{
    graphs::graph<std::size_t> result {m_dimension * m_dimension};

    std::random_device rd;
    std::uniform_int_distribution<std::size_t> dist(0, 99);
    for (std::size_t x { 0 }; x < m_dimension; x++) {
        for (std::size_t y { 0 }; y < m_dimension; y++) {
            if (x != (m_dimension - 1)) {
                result.set(pos(x, y), pos(x + 1,y), dist(rd));
            }
            if (y != (m_dimension - 1)) {
                result.set(pos(x, y), pos(x,y + 1), dist(rd));
            }
        }
    }

    m_graph = m_algorithm(result).remove_weight();
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
