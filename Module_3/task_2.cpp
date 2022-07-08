// Copyright 2022 by Artem Ustsov

/* 
* Дан невзвешенный неориентированный граф. 
* В графе может быть несколько кратчайших путей между какими-то вершинами. 
* Найдите количество различных кратчайших путей между заданными вершинами.
*
* Требования: сложность O(V+E). 
* Формат ввода.
* v: кол-во вершин (макс. 50000),
* n: кол-во ребер (макс. 200000),
* n пар реберных вершин,
* пара вершин u, w для запроса.
* Формат вывода.
* Количество кратчайших путей от u к w.
* 
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

class ListGraph {
public:
    ListGraph() = default;
    explicit ListGraph(const size_t& num_of_vertex) {
        adjacency_lists.resize(num_of_vertex);
    }
    ~ListGraph() = default;

    void add_edge(const size_t& from, const size_t& to) {
        adjacency_lists[from].push_back(to);
        adjacency_lists[to].push_back(from);
    }
    size_t count_min_paths(size_t from, size_t to);
private:
    std::vector<std::vector<size_t>> adjacency_lists;
};

size_t ListGraph::count_min_paths(size_t from, size_t to) {
    std::vector<size_t> distance(adjacency_lists.size(), SIZE_MAX);
    distance[from] = 0;

    std::vector<size_t> min_path_counter(adjacency_lists.size(), 0);
    min_path_counter[from] = 1;

    std::queue<size_t> q;
    q.push(from);

    while(!q.empty()) {
        size_t vertex = q.front();
        q.pop();
        for (const auto& neigh : adjacency_lists[vertex]) {
            // не знаем ни одного пути до этой вершины
            if (min_path_counter[neigh] == 0) {
                distance[neigh] = distance[vertex] + 1;
                min_path_counter[neigh] = min_path_counter[vertex];
                q.push(neigh);
            } else if (distance[neigh] == distance[vertex] + 1) { // есть другой способ дойти до соседа такой же длины
                min_path_counter[neigh] += min_path_counter[vertex]; // то добавляем кол-во способов дойти до родительской вершины
            }
        }
    }
    return min_path_counter[to];
}

int main() {
    size_t num_of_vertex = 0;
    size_t num_of_edges = 0;
    std::cin >> num_of_vertex >> num_of_edges;

    ListGraph ListGraph(num_of_vertex);
    size_t from = 0;
    size_t to = 0;
    for (size_t i = 0; i < num_of_edges; ++i) {
        std::cin >> from >> to;
        ListGraph.add_edge(from, to);
    }

    std::cin >> from >> to;
    std::cout << ListGraph.count_min_paths(from, to) << std::endl;
    return 0;
}
