#ifndef MAZE_H
#define MAZE_H

#include "graph.h"

#include <algorithm>
#include <iostream>
#include <random>
#include <thread>

namespace graphs {
class maze {
public:
    maze(std::size_t x, std::size_t y, bool colour = true);

    void print(std::ostream& out = std::cout) const;

    [[nodiscard]] auto graph() const -> graphs::graph<bool>;

private:
    void generate();
    void generate_graph();
    void generate_maze();
    [[nodiscard]] auto pos(std::size_t x, std::size_t y) const -> std::size_t;

    std::size_t m_x {};
    std::size_t m_y {};
    graphs::graph<bool> m_graph;
};

template <typename W, bool S, W D>
auto operator<<(std::ostream& stream, const maze& m) -> std::ostream&;

maze::maze(std::size_t x, std::size_t y, bool colour)
    : m_x { x }
    , m_y { y }
    , m_graph { x * y, colour }
{
    generate();
}

auto maze::pos(std::size_t x, std::size_t y) const -> std::size_t
{
    return m_x * y + x;
}

void maze::generate()
{
    generate_graph();
    generate_maze();
}

void maze::generate_graph()
{
    for (std::size_t x { 0 }; x < m_x; x++) {
        for (std::size_t y { 0 }; y < m_y; y++) {
            if (x < (m_x - 1)) {
                m_graph.set(pos(x, y), pos(x + 1, y));
            }
            if (y < (m_y - 1)) {
                m_graph.set(pos(x, y), pos(x, y + 1));
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

    std::shuffle(edges.begin(), edges.end(), g);

    std::size_t i { 0 };
    for (const auto& edge : edges) {
        m_graph.unset(edge.first, edge.second);
        if (!m_graph.connected_bi_bfs(edge.first, edge.second)) {
            m_graph.set(edge.first, edge.second);
        }
        i++;
    }
}

void maze::print(std::ostream& out) const
{
    for (std::size_t y { 0 }; y < m_y; y++) {
        for (std::size_t x { 0 }; x < m_x; x++) {
            if (x < (m_x - 1)) {
                if (m_graph.weight(pos(x, y), pos(x + 1, y))) {
                    out << "·-";
                } else {
                    out << "· ";
                }
            } else {
                out << "·";
            }
        }
        out << '\n';
        for (std::size_t x { 0 }; x < m_x; x++) {
            if (y < (m_y - 1)) {
                if (m_graph.weight(pos(x, y), pos(x, y + 1))) {
                    out << "| ";
                } else {
                    out << "  ";
                }
            }
        }
        out << '\n';
    }
}

auto maze::graph() const -> graphs::graph<bool>
{
    return m_graph;
}

auto operator<<(std::ostream& stream, const maze& m) -> std::ostream&
{
    m.print(stream);
    return stream;
}
}

#endif // MAZE_H
