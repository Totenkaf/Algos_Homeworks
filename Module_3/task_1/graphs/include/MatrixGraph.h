// Copyright 2022 by Artem Ustsov

#pragma once
#include "IGraph.h"

// Граф, хранящийся в виде матрицы смежности
class MatrixGraph : public IGraph {
public:
    explicit MatrixGraph(size_t size);
    explicit MatrixGraph(const IGraph& graph);
    ~MatrixGraph() 
    {}
    void add_edge(size_t from, size_t to) override;
    size_t vertices_count() const override;

    std::vector<size_t> get_next_vertices(size_t vertex) const override;
    std::vector<size_t> get_prev_vertices(size_t vertex) const override;
private:
   std::vector<std::vector<bool>> adjacency_matrix;
};
