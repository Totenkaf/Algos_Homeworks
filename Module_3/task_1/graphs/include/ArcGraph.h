// Copyright 2022 by Artem Ustsov

#pragma once
#include "IGraph.h"

typedef std::pair<size_t, size_t> edge;

// Граф, хранящийся в виде вектора пар концов ребер
class ArcGraph : public IGraph {
public:
    explicit ArcGraph(size_t size);
    explicit ArcGraph(const IGraph& graph);
    ~ArcGraph() 
    {}
    void add_edge(size_t from, size_t to) override;
    size_t vertices_count() const override;

    std::vector<size_t> get_next_vertices(size_t vertex) const override;
    std::vector<size_t> get_prev_vertices(size_t vertex) const override;
private:
   std::vector<edge> vector_of_pairs;
   size_t vertix_count;
};
