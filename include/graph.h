#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>
#include <array>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <ostream>
#include <stack>
#include <type_traits>
#include <vector>
#include <map>
#include <cassert>
#include <memory>

namespace graphs {

template <typename W = bool, bool S = true, W D = 1>
class graph {
    static_assert(std::is_integral<W>::value);

public:
    graph(const std::vector<std::vector<W>>& matrix);
    graph(std::size_t dimension);

    void set(std::size_t i, std::size_t j, W weight = D);

    void unset(std::size_t i, std::size_t j);

    auto remove_weight() const -> graph< bool>;

    [[nodiscard]] auto neighbours(std::size_t i) const -> std::map<std::size_t, W>;

    [[nodiscard]] auto weight(std::size_t i, std::size_t j) const -> W;

    [[nodiscard]] auto dimension() const -> std::size_t;

    [[nodiscard]] auto rank(std::size_t j) const -> std::size_t;

    [[nodiscard]] auto connected(std::size_t start, std::size_t end) const -> bool;

    void print(std::ostream& stream = std::cout) const;

private:
    [[nodiscard]] auto pos(std::size_t i, std::size_t j) const -> std::size_t;

    std::vector<W> m_edges {};
    std::size_t m_dimension {};
};

template <typename W, bool S, W D>
auto operator<<(std::ostream& stream, const graph<W, S, D>& g) -> std::ostream&;
}

//////////////////////
/// implementation ///
//////////////////////

namespace graphs {
template <typename W, bool S, W D>
graph<W, S, D>::graph(const std::vector<std::vector<W>>& matrix)
    : m_dimension { matrix.size()}
{
    m_edges.resize(dimension() * dimension());
    for (std::size_t i { 0 }; i < dimension(); i++) {
        assert(matrix[i].size() == dimension());
        for (std::size_t j { 0 }; j < dimension(); j++) {
            if (S && (matrix[i][j] != matrix[j][i])) {
                std::cerr<<"Matrix is not symmetric.\n"
                        <<"a_"<<std::to_string(i)<<','<<std::to_string(j)<<'='<<std::to_string(matrix[i][j])<<'\n'
                        <<"a_"<<std::to_string(j)<<','<<std::to_string(i)<<'='<<std::to_string(matrix[j][i])<<'\n';
                assert(matrix[i][j] == matrix[j][i]);
            }
            m_edges[pos(i, j)] = matrix[i][j];
        }
    }
}

template <typename W, bool S, W D>
graph<W, S, D>::graph(std::size_t dimension)
    : m_dimension { dimension }
{
    m_edges.resize(m_dimension * m_dimension);
}

template <typename W, bool S, W D>
void graph<W, S, D>::set(std::size_t i, std::size_t j, W weight)
{
    if (S) {
        m_edges[pos(j, i)] = weight;
    }
    m_edges[pos(std::move(i), std::move(j))] = std::move(weight);
}

template <typename W, bool S, W D>
void graph<W, S, D>::unset(std::size_t i, std::size_t j)
{
    set(std::move(i), std::move(j), 0);
}

template <typename W, bool S, W D>
auto  graph<W, S, D>::remove_weight() const -> graph< bool>
{
    graph<bool> result {m_dimension};

    for (std::size_t i { 0 }; i < m_dimension; i++) {
        for (std::size_t j { 0 }; j < m_dimension; j++) {
            if (weight(i, j) != 0) {
                result.set(i, j);
            }
        }
    }

    return result;
}

template <typename W, bool S, W D>
auto graph<W, S, D>::neighbours(std::size_t j) const -> std::map<std::size_t, W>
{
    std::map<std::size_t, W> neighbours {};

    for (std::size_t i { 0 }; i < m_dimension; i++) {
        if (weight(i, j) != 0) {
            neighbours.emplace(i, weight(i, j));
        }
    }
    return neighbours;
}

template <typename W, bool S, W D>
auto graph<W, S, D>::weight(std::size_t i, std::size_t j) const -> W
{
    return m_edges[pos(std::move(i), std::move(j))];
}

template <typename W, bool S, W D>
auto graph<W, S, D>::dimension() const -> std::size_t
{
    return m_dimension;
}

template <typename W, bool S, W D>
auto graph<W, S, D>::rank(std::size_t j) const -> std::size_t
{
    return std::accumulate(m_edges.begin() + pos(0, j), m_edges.begin() + pos(m_dimension - 1, j), 0, [](W first, W second) {
        return (second != 0) ? (first + second) : first;
    });
}

template <typename W, bool S, W D>
auto graph<W, S, D>::pos(std::size_t i, std::size_t j) const -> std::size_t
{
    return m_dimension * j + i;
}

template <typename W, bool S, W D>
void graph<W, S, D>::print(std::ostream& stream) const
{
    stream << std::setfill(' ');
    for (std::size_t i { 0 }; i < m_dimension; i++) {
        for (std::size_t j { 0 }; j < m_dimension; j++) {
            if (weight(i, j) == 0) {
                stream << "";
            } else {
                stream << "\033[1;31m";
            }
            stream << ' ' << std::setw(2) << weight(i, j)<<"\033[0m";
        }
        stream << '\n';
    }
}

template <typename W, bool S, W D>
auto graph<W, S, D>::connected(std::size_t start, std::size_t end) const -> bool
{
    std::stack<std::size_t> stack {};
    stack.emplace(start);

    std::vector<std::size_t> unvisited {};
    unvisited.resize(m_dimension);
    std::iota(unvisited.begin(), unvisited.end(), 0);

    for (std::size_t i { stack.top() }; !stack.empty();) {
        unvisited.erase(std::find(unvisited.begin(), unvisited.end(), i));
        stack.pop();
        if (i == end) {
            return true;
        }

        for (const auto& j : unvisited) {
            if (weight(i, j) != 0) {
                stack.emplace(j);
            }
        }
        i = stack.top();
    }
    return false;
}

template <typename W, bool S, W D>
auto operator<<(std::ostream& stream, const graph<W, S, D>& g) -> std::ostream&
{
    g.print(stream);
    return stream;
}

}

#endif // GRAPH_H
