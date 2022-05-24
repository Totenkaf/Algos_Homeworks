// Copyright 2022 by Artem Ustsov

#pragma once
#include "IGraph.h"

// Граф, хранящийся в хеш-таблицы
class SetGraph : public IGraph {
public:
    explicit SetGraph(int size);
    explicit SetGraph(const IGraph& graph);
    ~SetGraph() 
    {}
    void add_edge(size_t from, size_t to) override;
    size_t vertices_count() const override;

    std::vector<int> get_next_vertices(int vertex) const override;
    std::vector<int> get_prev_vertices(int vertex) const override;
private:
   std::vector<std::set<int>> vector_of_sets;
};
