// Copyright 2022 by Artem Ustsov

#include "SetGraph.h"

SetGraph::SetGraph(size_t size): 
vector_of_sets(size) 
{}

SetGraph::SetGraph(const IGraph& graph): 
vector_of_sets(graph.vertices_count()) {
    for (size_t from = 0; from < vector_of_sets.size(); ++from) {
        for (const auto& to : graph.get_next_vertices(from)) {
            vector_of_sets[from].insert(to);
        }
    }
}

void SetGraph::add_edge(size_t from, size_t to) {
    assert(from < vector_of_sets.size());
    assert(to < vector_of_sets.size());
    vector_of_sets[from].insert(to);
}

size_t SetGraph::vertices_count() const {
    return vector_of_sets.size();
}

std::vector<size_t> SetGraph::get_next_vertices(size_t vertex) const {
    assert(vertex < vector_of_sets.size());
    std::vector<size_t> neighbors;
    for (const auto& to : vector_of_sets[vertex]) {
        neighbors.push_back(to);
    }
    return neighbors;
}

std::vector<size_t> SetGraph::get_prev_vertices(size_t vertex) const {
    assert(vertex < vector_of_sets.size());
    std::vector<size_t> result;
    for (size_t from = 0; from < vector_of_sets.size(); ++from) {
        if (vector_of_sets[from].find(vertex) != vector_of_sets[from].end()) {
            result.push_back(from);
            break;
        }
    }
    return result;
}
