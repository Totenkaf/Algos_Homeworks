// Copyright 2022 by Artem Ustsov

#pragma once
#include "IGraph.h"

// Граф, хранящийся в хеш-таблицы
class SetGraph : public IGraph {
public:
    explicit SetGraph(size_t size);
    explicit SetGraph(const IGraph& graph);
    ~SetGraph() 
    {}
    void add_edge(size_t from, size_t to) override;
    size_t vertices_count() const override;

    std::vector<size_t> get_next_vertices(size_t vertex) const override;
    std::vector<size_t> get_prev_vertices(size_t vertex) const override;
private:
   std::vector<std::set<size_t>> vector_of_sets;
};
