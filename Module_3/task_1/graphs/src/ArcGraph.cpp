// Copyright 2022 by Artem Ustsov

#include "ArcGraph.h"

ArcGraph::ArcGraph(size_t size)
: vertix_count(size) 
{}

ArcGraph::ArcGraph(const IGraph& graph) {
    vertix_count = graph.vertices_count();
    for (size_t from = 0; from < vertix_count; ++from) {
        for (const auto& to : graph.get_next_vertices(from)) {
            vector_of_pairs.emplace_back(from, to);
        }
    }
}

void ArcGraph::add_edge(size_t from, size_t to) {
    assert(from < vertix_count);
    assert(to < vertix_count);
    vector_of_pairs.emplace_back(from, to);
}

size_t ArcGraph::vertices_count() const {
    return vertix_count;
}

std::vector<size_t> ArcGraph::get_next_vertices(size_t vertex) const {
    assert(vertex < vertix_count);
    std::vector<size_t> neighbors;
    for (const auto& pair : vector_of_pairs) {
        if (pair.first == vertex) {
            neighbors.push_back(pair.second);
        }
    }
    return neighbors;
}

std::vector<size_t> ArcGraph::get_prev_vertices(size_t vertex) const {
    assert(vertex < vertix_count);
    std::vector<size_t> result;
    for (const auto& pair : vector_of_pairs) {
        if (pair.second == vertex) {
            result.push_back(pair.first);
        }
    }
    return result;
}
