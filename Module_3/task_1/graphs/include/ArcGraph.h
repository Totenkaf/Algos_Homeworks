// Copyright 2022 by Artem Ustsov

#pragma once
#include "IGraph.h"

typedef std::pair<int, int> edge;

// Граф, хранящийся в виде вектора пар концов ребер
class ArcGraph : public IGraph {
public:
    explicit ArcGraph(int size);
    explicit ArcGraph(const IGraph& graph);
    ~ArcGraph() 
    {}
    void add_edge(size_t from, size_t to) override;
    size_t vertices_count() const override;

    std::vector<int> get_next_vertices(int vertex) const override;
    std::vector<int> get_prev_vertices(int vertex) const override;
private:
   std::vector<edge> vector_of_pairs;
   int vertix_count;
};
