// Copyright 2022 by Artem Ustsov

#include "graphs/include/ListGraph.h"
#include <iostream>

int main(void) {
    ListGraph graph(10);
    graph.add_edge(0,1);
    graph.add_edge(0,5);
    graph.add_edge(1,2);
    graph.add_edge(1,3);
    graph.add_edge(1,5);
    graph.add_edge(1,6);
    graph.add_edge(3,2);
    graph.add_edge(3,4);
    graph.add_edge(3,6);
    graph.add_edge(5,4);
    graph.add_edge(5,6);
    graph.add_edge(6,4);

    graph.add_edge(7,8);
    graph.add_edge(8,9);

    utils::main_BFS(graph, [](int vertex){std::cout << vertex << " ";});
    std::cout << std::endl;
    utils::main_DFS(graph, [](int vertex){std::cout << vertex << " ";});
    std::cout << std::endl;
    return 0;
}
