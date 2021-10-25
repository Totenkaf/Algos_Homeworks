#include "AbstractGraph.h"

#include <vector>
using std::vector;
#include <iostream>
using std::cout;
using std::endl;

class ListGraph : public AbstractGraph {
public:
    ListGraph(int vertexCount);
    ListGraph(const AbstractGraph& graph);

    virtual void AddEdge(int from, int to) override;

    virtual int VerticesCount() const override;
    virtual vector<int> GetNextVertices(int vertex) const override;
    virtual vector<int> GetPrevVertices(int vertex) const override;

private:
    vector<vector<int>> adjacencyLists;
};

ListGraph::ListGraph(int vertexCount) {
    adjacencyLists.resize(vertexCount);
}

ListGraph::ListGraph(const AbstractGraph& graph) {
    adjacencyLists.resize(graph.VerticesCount());
    for (int from = 0; from < adjacencyLists.size(); from++)
        adjacencyLists[from] = graph.GetNextVertices(from);
}

void ListGraph::AddEdge(int from, int to) {
    if ((from < 0 || from >= adjacencyLists.size()) ||
        (to < 0 || to >= adjacencyLists.size()))
        return;

    adjacencyLists[from].push_back(to);
}

int ListGraph::VerticesCount() const {
    return adjacencyLists.size();
}

vector<int> ListGraph::GetNextVertices(int vertex) const {
    if (vertex < 0 || vertex >= adjacencyLists.size())
        throw std::exception();

    return adjacencyLists[vertex];
}

vector<int> ListGraph::GetPrevVertices(int vertex) const {
    if (vertex < 0 || vertex >= adjacencyLists.size())
        throw std::exception();

    vector<int> result;
    for(int from = 0; from < adjacencyLists.size(); from++) {
        for(int i = 0; i < adjacencyLists[from].size(); i++) {
            if (adjacencyLists[from][i] == vertex) {
                result.push_back(from);
                break;
            }
        }
    }
    return result;
}
