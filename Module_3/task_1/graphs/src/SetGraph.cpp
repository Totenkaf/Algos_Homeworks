// Copyright 2022 by Artem Ustsov

#include "SetGraph.h"

SetGraph::SetGraph(int size): 
vector_of_sets(size) 
{}

SetGraph::SetGraph(const IGraph& graph): 
vector_of_sets(graph.vertices_count()) {
    for (size_t from = 0; from < vector_of_sets.size(); ++from) {
        for (const auto& to : graph.get_next_vertices(from)) {
            vector_of_sets[from].insert((int)to);
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

std::vector<int> SetGraph::get_next_vertices(int vertex) const {
    assert(vertex < (int)vector_of_sets.size());
    std::vector<int> neighbors;
    for (const auto& to : vector_of_sets[vertex]) {
        neighbors.push_back((int)to);
    }
    return neighbors;
}

std::vector<int> SetGraph::get_prev_vertices(int vertex) const {
    assert(vertex < (int)vector_of_sets.size());
    std::vector<int> result;
    for (size_t from = 0; from < vector_of_sets.size(); ++from) {
        if (vector_of_sets[from].find(vertex) != vector_of_sets[from].end()) {
            result.push_back((int)from);
            break;
        }
    }
    return result;
}
