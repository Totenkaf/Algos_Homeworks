// Copyright 2022 by Artem Ustsov

#include "ArcGraph.h"

ArcGraph::ArcGraph(int size)
: vertix_count(size) 
{}

ArcGraph::ArcGraph(const IGraph& graph) {
    vertix_count = (int)graph.vertices_count();
    for (int from = 0; from < vertix_count; ++from) {
        for (const auto& to : graph.get_next_vertices(from)) {
            vector_of_pairs.emplace_back(from, to);
        }
    }
}

void ArcGraph::add_edge(size_t from, size_t to) {
    assert((int)from < vertix_count);
    assert((int)to < (int)vertix_count);
    vector_of_pairs.emplace_back((int)from, (int)to);
}

size_t ArcGraph::vertices_count() const {
    return vertix_count;
}

std::vector<int> ArcGraph::get_next_vertices(int vertex) const {
    assert(vertex < (int)vertix_count);
    std::vector<int> neighbors;
    for (const auto& pair : vector_of_pairs) {
        if (pair.first == vertex) {
            neighbors.push_back(pair.second);
        }
    }
    return neighbors;
}

std::vector<int> ArcGraph::get_prev_vertices(int vertex) const {
    assert(vertex < (int)vertix_count);
    std::vector<int> result;
    for (const auto& pair : vector_of_pairs) {
        if (pair.second == vertex) {
            result.push_back(pair.first);
        }
    }
    return result;
}
