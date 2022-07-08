// Copyright 2022 by Artem Ustsov

/*
 * Требуется отыскать самый короткий маршрут между городами.
 * Из города может выходить дорога, которая возвращается в этот же город.
 * Требуемое время работы O((N + M)log N), где N – количество городов,
 * M – известных дорог между ними.
 * N ≤ 10000, M ≤ 250000.
 * Длина каждой дороги ≤ 10000.
 * 
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

typedef std::pair<size_t, size_t> Edge;

class ArcGraph {
public:
    ArcGraph() = default;
    explicit ArcGraph(const size_t& num_of_vertex) {
        neighbors.resize(num_of_vertex);
    }
    ~ArcGraph() = default;
    void add_edge(const size_t& from, const size_t& to, const size_t& distance) {
        neighbors[from].edges.emplace_back(Edge(distance, to));
        neighbors[to].edges.emplace_back(Edge(distance, from));
    }
    size_t dijkstra_traverse(size_t from, size_t to);
private:
    struct Neighbors {
        std::vector<Edge> edges;
    };
    std::vector<Neighbors> neighbors;
};

size_t ArcGraph::dijkstra_traverse(size_t from, size_t to) {
    std::vector<size_t> distance(neighbors.size(), SIZE_MAX);
    distance[from] = 0;

    std::multiset<Edge> q;
    q.insert(Edge(distance[from], from));

    while(!q.empty()) {
        size_t vertex = q.begin()->second;
        q.erase(q.begin());
        for (const auto& neighbor : neighbors[vertex].edges) {
            if (distance[neighbor.second] > distance[vertex] + neighbor.first) {
                if (distance[vertex] != SIZE_MAX)
                    q.erase(Edge(distance[vertex], vertex));
                distance[neighbor.second] = distance[vertex] + neighbor.first;
                q.insert(Edge(neighbor.first, neighbor.second));
            }
        }
    }
    return distance[to];
}

int main() {
    size_t num_of_vertex = 0;
    size_t num_of_edges = 0;
    std::cin >> num_of_vertex >> num_of_edges;

    ArcGraph ArcGraph(num_of_vertex);
    size_t from = 0;
    size_t to = 0;
    size_t distance = 0;
    for (size_t i = 0; i < num_of_edges; ++i) {
        std::cin >> from >> to >> distance;
        ArcGraph.add_edge(from, to, distance);
    }

    std::cin >> from >> to;
    std::cout << ArcGraph.dijkstra_traverse(from, to) << std::endl;
    return 0;
}