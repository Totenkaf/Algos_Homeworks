// Copyright 2022 by Artem Ustsov

#pragma once
#include <cassert>
#include <functional>
#include <queue>
#include <set>
#include <vector>

class IGraph {
public:
    virtual ~IGraph()
    {}
    
    // Добавление ребра от from к to.
    virtual void add_edge(size_t from, size_t to) = 0;
    virtual size_t vertices_count() const = 0;

    virtual std::vector<int> get_next_vertices(int vertex) const = 0;
    virtual std::vector<int> get_prev_vertices(int vertex) const = 0;   
};


namespace utils {
    void BFS_traverse(const IGraph& graph, int vertex, std::vector<bool> &visited, 
                    const std::function<void(int)> &func);
    void main_BFS(const IGraph& graph, const std::function<void(int)>& func);

    void DFS_traverse(const IGraph& graph, int vertex, std::vector<bool> &visited, 
                    const std::function<void(int)> &func);
    void main_DFS(const IGraph& graph, const std::function<void(int)>& func);
}
