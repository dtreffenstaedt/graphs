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

namespace graphs {

template <std::size_t N, typename W = bool, bool S = true, W D = 1>
class graph {
    static_assert(std::is_integral<W>::value);

public:
    graph(const std::array<std::array<W, N>, N>& matrix);
    graph(const std::array<W, N * N>& matrix);
    graph();

    constexpr void set(std::size_t i, std::size_t j, W weight = D);

    constexpr void unset(std::size_t i, std::size_t j);

    [[nodiscard]] auto neighbours(std::size_t i) const -> std::map<std::size_t, W>;

    [[nodiscard]] constexpr auto weight(std::size_t i, std::size_t j) const -> W;

    [[nodiscard]] constexpr auto n() const -> std::size_t;

    [[nodiscard]] constexpr auto rank(std::size_t j) const -> std::size_t;

    [[nodiscard]] auto connected(std::size_t start, std::size_t end) const -> bool;

    void print(std::ostream& stream = std::cout) const;

private:
    [[nodiscard]] constexpr auto pos(std::size_t i, std::size_t j) const -> std::size_t;

    std::array<W, N * N> m_edges { 0 };
};

template <std::size_t N, typename W, bool S, W D>
auto operator<<(std::ostream& stream, const graph<N, W, S, D>& g) -> std::ostream&;
}

//////////////////////
/// implementation ///
//////////////////////

namespace graphs {
template <std::size_t N, typename W, bool S, W D>
graph<N, W, S, D>::graph(const std::array<std::array<W, N>, N>& matrix)
{
    for (std::size_t i { 0 }; i < N; i++) {
        for (std::size_t j { 0 }; j < N; j++) {
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

template <std::size_t N, typename W, bool S, W D>
graph<N, W, S, D>::graph(const std::array<W, N * N>& matrix)
    : m_edges { matrix }
{
}

template <std::size_t N, typename W, bool S, W D>
graph<N, W, S, D>::graph() = default;

template <std::size_t N, typename W, bool S, W D>
constexpr void graph<N, W, S, D>::set(std::size_t i, std::size_t j, W weight)
{
    if (S) {
        m_edges[pos(j, i)] = weight;
    }
    m_edges[pos(std::move(i), std::move(j))] = std::move(weight);
}

template <std::size_t N, typename W, bool S, W D>
constexpr void graph<N, W, S, D>::unset(std::size_t i, std::size_t j)
{
    set(std::move(i), std::move(j), 0);
}

template <std::size_t N, typename W, bool S, W D>
auto graph<N, W, S, D>::neighbours(std::size_t j) const -> std::map<std::size_t, W>
{
    std::map<std::size_t, W> neighbours {};

    for (std::size_t i { 0 }; i < N; i++) {
        if (weight(i, j) != 0) {
            neighbours.emplace(i, weight(i, j));
        }
    }
    return neighbours;
}

template <std::size_t N, typename W, bool S, W D>
constexpr auto graph<N, W, S, D>::weight(std::size_t i, std::size_t j) const -> W
{
    return m_edges[pos(std::move(i), std::move(j))];
}

template <std::size_t N, typename W, bool S, W D>
constexpr auto graph<N, W, S, D>::n() const -> std::size_t
{
    return N;
}

template <std::size_t N, typename W, bool S, W D>
constexpr auto graph<N, W, S, D>::rank(std::size_t j) const -> std::size_t
{
    return std::accumulate(m_edges.begin() + pos(0, j), m_edges.begin() + pos(N - 1, j), 0, [](W first, W second) {
        return (second != 0) ? (first + second) : first;
    });
}

template <std::size_t N, typename W, bool S, W D>
constexpr auto graph<N, W, S, D>::pos(std::size_t i, std::size_t j) const -> std::size_t
{
    return N * j + i;
}

template <std::size_t N, typename W, bool S, W D>
void graph<N, W, S, D>::print(std::ostream& stream) const
{
    stream << std::setfill(' ');
    for (std::size_t i { 0 }; i < N; i++) {
        for (std::size_t j { 0 }; j < N; j++) {
            if (weight(i, j) == 0) {
                stream << "   ";
            } else {
                stream << ' ' << std::setw(2) << weight(i, j);
            }
        }
        stream << '\n';
    }
}

template <std::size_t N, typename W, bool S, W D>
auto graph<N, W, S, D>::connected(std::size_t start, std::size_t end) const -> bool
{
    std::stack<std::size_t> stack {};
    stack.emplace(start);

    std::vector<std::size_t> unvisited {};
    unvisited.resize(N);
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

template <std::size_t N, typename W, bool S, W D>
auto operator<<(std::ostream& stream, const graph<N, W, S, D>& g) -> std::ostream&
{
    g.print(stream);
    return stream;
}

}

#endif // GRAPH_H
