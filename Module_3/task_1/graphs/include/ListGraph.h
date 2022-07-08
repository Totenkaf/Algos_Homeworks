// Copyright 2022 by Artem Ustsov

#pragma once
#include "IGraph.h"

// Граф, хранящийся в виде списка смежности
class ListGraph : public IGraph {
public:
    explicit ListGraph(size_t size);
    explicit ListGraph(const IGraph& graph);
    ~ListGraph() = default;
    void add_edge(size_t from, size_t to) override;
    size_t vertices_count() const override;

    std::vector<size_t> get_next_vertices(size_t vertex) const override;
    std::vector<size_t> get_prev_vertices(size_t vertex) const override;
private:
   std::vector<std::vector<size_t>> adjacency_lists;
};
