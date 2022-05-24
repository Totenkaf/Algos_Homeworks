// Copyright 2022 by Artem Ustsov

#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(size_t size)
: adjacency_matrix(size) {
    for (size_t i = 0; i < adjacency_matrix.size(); ++i) {
        adjacency_matrix[i].resize(size);
        std::fill(adjacency_matrix[i].begin(), adjacency_matrix[i].end(), 0);
    }
}

MatrixGraph::MatrixGraph(const IGraph& graph)
: adjacency_matrix(graph.vertices_count()){
    size_t size = graph.vertices_count();
    for (size_t from = 0; from < size; ++from) {
        adjacency_matrix[from].resize(size);
        auto neighbors = graph.get_next_vertices(from);
        for (const auto& to : neighbors) {
            adjacency_matrix[from][to] = 1;
        }
    }
}

void MatrixGraph::add_edge(size_t from, size_t to) {
    assert(to < adjacency_matrix.size());
    assert(from < adjacency_matrix.size());
    adjacency_matrix[from][to] = 1;
}

size_t MatrixGraph::vertices_count() const {
    return adjacency_matrix.size();
}

std::vector<size_t> MatrixGraph::get_next_vertices(size_t vertex) const {
    assert(vertex < adjacency_matrix.size());
    std::vector<size_t> neighbors;
    for (size_t to = 0; to < adjacency_matrix.size(); ++to) {
        if (adjacency_matrix[vertex][to] == 1)
            neighbors.push_back(to);
    }
    return neighbors;
}

std::vector<size_t> MatrixGraph::get_prev_vertices(size_t vertex) const {
    assert(vertex < adjacency_matrix.size());
    std::vector<size_t> result;
    for (size_t from = 0; from < adjacency_matrix.size(); ++from) {
        if (adjacency_matrix[from][vertex] == 1)
            result.push_back(from);
    }
    return result;
}
