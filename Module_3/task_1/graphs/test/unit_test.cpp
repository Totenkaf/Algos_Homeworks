// Copyright 2022 by Artem Ustsov

#include "ArcGraph.h"
#include "IGraph.h"
#include "ListGraph.h"
#include "MatrixGraph.h"
#include "SetGraph.h"
#include <gtest/gtest.h>
#include <fstream>

class GraphEnvironment : public ::testing::Test {
public:
    ListGraph list_graph = ListGraph(10);
    MatrixGraph matrix_graph = MatrixGraph(10);
    SetGraph set_graph = SetGraph(10);
    ArcGraph arc_graph = ArcGraph(10);

    std::vector<IGraph*> graphs = { 
                                    &list_graph, 
                                    &matrix_graph,
                                    &set_graph,
                                    &arc_graph
                                  };
    void SetUp() override {
        for (const auto& graph : graphs) {
            graph->add_edge(0,1);
            graph->add_edge(0,5);
            graph->add_edge(1,2);
            graph->add_edge(1,3);
            graph->add_edge(1,5);
            graph->add_edge(1,6);
            graph->add_edge(3,2);
            graph->add_edge(3,4);
            graph->add_edge(3,6);
            graph->add_edge(5,4);
            graph->add_edge(5,6);
            graph->add_edge(6,4);

            graph->add_edge(7,8);
            graph->add_edge(8,9);
        }
    }
    virtual ~GraphEnvironment()
    {}
};

TEST_F(GraphEnvironment, add_test) {
    EXPECT_EQ(list_graph.vertices_count(), 10);
    EXPECT_EQ(matrix_graph.vertices_count(), 10);
    EXPECT_EQ(set_graph.vertices_count(), 10);
    EXPECT_EQ(arc_graph.vertices_count(), 10);
}

TEST_F(GraphEnvironment, graphs_BFS_test) {
    std::vector<size_t> true_bfs_results = {0, 1, 5, 2, 3, 6, 4, 7, 8, 9};

    std::vector<size_t> result_list_graph_BFS;
    utils::main_BFS(list_graph, [&result_list_graph_BFS](size_t vertex) { result_list_graph_BFS.push_back(vertex); });
    for (size_t i = 0; i < result_list_graph_BFS.size(); ++i) {
        EXPECT_EQ(result_list_graph_BFS[i], true_bfs_results[i]);
    }

    std::vector<size_t> result_matrix_graph_BFS;
    utils::main_BFS(list_graph, [&result_matrix_graph_BFS](size_t vertex) { result_matrix_graph_BFS.push_back(vertex); });
    for (size_t i = 0; i < result_matrix_graph_BFS.size(); ++i) {
        EXPECT_EQ(result_matrix_graph_BFS[i], true_bfs_results[i]);
    }

    std::vector<size_t> result_set_graph_BFS;
    utils::main_BFS(list_graph, [&result_set_graph_BFS](size_t vertex) { result_set_graph_BFS.push_back(vertex); });
    for (size_t i = 0; i < result_set_graph_BFS.size(); ++i) {
        EXPECT_EQ(result_set_graph_BFS[i], true_bfs_results[i]);
    }

    std::vector<size_t> result_arc_graph_BFS;
    utils::main_BFS(list_graph, [&result_arc_graph_BFS](size_t vertex) { result_arc_graph_BFS.push_back(vertex); });
    for (size_t i = 0; i < result_arc_graph_BFS.size(); ++i) {
        EXPECT_EQ(result_arc_graph_BFS[i], true_bfs_results[i]);
    }
}

TEST_F(GraphEnvironment, graphs_DFS_test) {
    std::vector<size_t> true_dfs_results = {0, 1, 2, 3, 4, 6, 5, 7, 8, 9};

    std::vector<size_t> result_list_graph_BFS;
    utils::main_DFS(list_graph, [&result_list_graph_BFS](size_t vertex) { result_list_graph_BFS.push_back(vertex); });
    for (size_t i = 0; i < result_list_graph_BFS.size(); ++i) {
        EXPECT_EQ(result_list_graph_BFS[i], true_dfs_results[i]);
    }

    std::vector<size_t> result_matrix_graph_BFS;
    utils::main_DFS(list_graph, [&result_matrix_graph_BFS](size_t vertex) { result_matrix_graph_BFS.push_back(vertex); });
    for (size_t i = 0; i < result_matrix_graph_BFS.size(); ++i) {
        EXPECT_EQ(result_matrix_graph_BFS[i], true_dfs_results[i]);
    }

    std::vector<size_t> result_set_graph_BFS;
    utils::main_DFS(list_graph, [&result_set_graph_BFS](size_t vertex) { result_set_graph_BFS.push_back(vertex); });
    for (size_t i = 0; i < result_set_graph_BFS.size(); ++i) {
        EXPECT_EQ(result_set_graph_BFS[i], true_dfs_results[i]);
    }

    std::vector<size_t> result_arc_graph_BFS;
    utils::main_DFS(list_graph, [&result_arc_graph_BFS](size_t vertex) { result_arc_graph_BFS.push_back(vertex); });
    for (size_t i = 0; i < result_arc_graph_BFS.size(); ++i) {
        EXPECT_EQ(result_arc_graph_BFS[i], true_dfs_results[i]);
    }
}

TEST_F(GraphEnvironment, direct_copy_test) {
    std::vector<size_t> result_list_graph_BFS;
    utils::main_BFS(list_graph, [&result_list_graph_BFS](size_t vertex) { result_list_graph_BFS.push_back(vertex); });

    ListGraph list_graph_2(list_graph); // direct copy via copy constructor

    std::vector<size_t> result_list_graph_2_BFS;
    utils::main_BFS(list_graph, [&result_list_graph_2_BFS](size_t vertex) { result_list_graph_2_BFS.push_back(vertex); });

    for (size_t i = 0; i < result_list_graph_2_BFS.size(); ++i) {
        EXPECT_EQ(result_list_graph_2_BFS[i], result_list_graph_BFS[i]);
    }
}

TEST_F(GraphEnvironment, crossed_copy_test) {
    std::vector<size_t> result_list_graph_BFS;
    utils::main_BFS(list_graph, [&result_list_graph_BFS](size_t vertex) { result_list_graph_BFS.push_back(vertex); });

    ArcGraph arc_graph_2(list_graph); // crossed copy via polimorphism and copy constructor

    std::vector<size_t> result_arc_graph_2_BFS;
    utils::main_BFS(list_graph, [&result_arc_graph_2_BFS](size_t vertex) { result_arc_graph_2_BFS.push_back(vertex); });

    for (size_t i = 0; i < result_arc_graph_2_BFS.size(); ++i) {
        EXPECT_EQ(result_arc_graph_2_BFS[i], result_list_graph_BFS[i]);
    }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
