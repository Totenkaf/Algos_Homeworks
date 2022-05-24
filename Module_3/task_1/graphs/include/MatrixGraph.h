// Copyright 2022 by Artem Ustsov

#pragma once
#include "IGraph.h"

// Граф, хранящийся в виде матрицы смежности
class MatrixGraph : public IGraph {
public:
    explicit MatrixGraph(int size);
    explicit MatrixGraph(const IGraph& graph);
    ~MatrixGraph() 
    {}
    void add_edge(size_t from, size_t to) override;
    size_t vertices_count() const override;

    std::vector<int> get_next_vertices(int vertex) const override;
    std::vector<int> get_prev_vertices(int vertex) const override;
private:
   std::vector<std::vector<bool>> adjacency_matrix;
};
