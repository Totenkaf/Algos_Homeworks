// Copyright 2022 by Artem Ustsov

#pragma once
#include "IGraph.h"

// Граф, хранящийся в виде списка смежности
class ListGraph : public IGraph {
public:
    explicit ListGraph(int size);
    explicit ListGraph(const IGraph& graph);
    ~ListGraph() 
    {}
    void add_edge(size_t from, size_t to) override;
    size_t vertices_count() const override;

    std::vector<int> get_next_vertices(int vertex) const override;
    std::vector<int> get_prev_vertices(int vertex) const override;
private:
   std::vector<std::vector<int>> adjacency_lists;
};
