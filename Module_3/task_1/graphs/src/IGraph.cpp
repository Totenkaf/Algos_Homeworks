// Copyright 2022 by Artem Ustsov

#include "IGraph.h"

void utils::BFS_traverse(const IGraph& graph, int vertex, std::vector<bool>& visited, 
                  const std::function<void(int)> &func) {
    std::queue<int> bfs_queue;
    bfs_queue.push(vertex);
    visited[vertex] = true;

    while (!bfs_queue.empty()) {
        int current = bfs_queue.front();
        bfs_queue.pop();
        func(current);
        auto neighbors = graph.get_next_vertices(current);
        for (const auto& neighbor : neighbors) {
            if (!visited[neighbor]) {
                bfs_queue.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }
    return;
}

void utils::main_BFS(const IGraph& graph, const std::function<void(int)> &func) {
    std::vector<bool> visited(graph.vertices_count(), false);
    for(size_t i = 0; i < graph.vertices_count(); ++i) {
        if(!visited[i]) {
            BFS_traverse(graph, i, visited, func);
        }
    }
    return;
}

void utils::DFS_traverse(const IGraph& graph, int vertex, std::vector<bool> &visited, 
                  const std::function<void(int)> &func) {

    visited[vertex] = true;
    func(vertex);

    for (const auto& neighbor : graph.get_next_vertices(vertex)) {
        if(!visited[neighbor]) {
            DFS_traverse(graph, neighbor, visited, func);
        }
    }
    
    return;
}


void utils::main_DFS(const IGraph& graph, const std::function<void(int)>& func) {
    std::vector<bool> visited(graph.vertices_count(), false);
    for(size_t i = 0; i < graph.vertices_count(); ++i) {
        if(!visited[i]) {
            DFS_traverse(graph, i, visited, func);
        }
    }
    return;
}
