#ifndef GRAPH_H
#define GRAPH_H

#include <array>
#include <cstdint>
#include <numeric>
#include <type_traits>
#include <vector>

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

    [[nodiscard]] auto neighbours(std::size_t i) const -> std::vector<std::size_t>;

    [[nodiscard]] constexpr auto weight(std::size_t i, std::size_t j) const -> W;

    [[nodiscard]] constexpr auto n() const -> std::size_t;

    [[nodiscard]] constexpr auto rank(std::size_t j) const -> std::size_t;

private:
    [[nodiscard]] constexpr auto pos(std::size_t i, std::size_t j) const -> std::size_t;

    std::array<W, N * N> m_edges { 0 };
};

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
auto graph<N, W, S, D>::neighbours(std::size_t j) const -> std::vector<std::size_t>
{
    std::vector<std::size_t> neighbours {};

    for (auto i { 0 }; i < N; i++) {
        if (i == j) {
            continue;
        }

        if (weight(i, j) != 0) {
            neighbours.emplace_back(i);
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

}

#endif // GRAPH_H
