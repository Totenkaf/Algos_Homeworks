// Copyright 2022 by Artem Ustsov

#include "ListGraph.h"

ListGraph::ListGraph(int size)
: adjacency_lists(size) 
{}

ListGraph::ListGraph(const IGraph& graph)
: adjacency_lists(graph.vertices_count()){
    for (size_t i = 0; i < adjacency_lists.size(); ++i) {
        adjacency_lists[i] = graph.get_next_vertices(i);
    }
}

void ListGraph::add_edge(size_t from, size_t to) {
    assert(to < adjacency_lists.size());
    assert(from < adjacency_lists.size());
    adjacency_lists[from].push_back(to);
    return;
}

size_t ListGraph::vertices_count() const {
    return adjacency_lists.size();
}

std::vector<int> ListGraph::get_next_vertices(int vertex) const {
    assert(vertex < (int)adjacency_lists.size()); // скастить по с++ стилю
    return adjacency_lists[vertex];
}

std::vector<int> ListGraph::get_prev_vertices(int vertex) const {
    assert(vertex < (int)adjacency_lists.size()); // скастить по с++ стилю
    std::vector<int> result;
    for (size_t from = 0; from < adjacency_lists.size(); ++from) {
        for (size_t i = 0; i < adjacency_lists[from].size(); ++i) {
            if (adjacency_lists[from][i] == vertex) {
                result.push_back(from);
                break;
            }
        }
    }
    return result;
}
