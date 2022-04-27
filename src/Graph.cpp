#include "Graph.h"

Graph::Graph(std::vector<Edge> const& edges, int n)
{
    // resize the vector to hold `n` elements of type `vector<int>`
    m_adjList.resize(n);

    // add edges to the directed graph
    for (auto& edge : edges)
    {
        // insert at the end
        m_adjList[edge.src].push_back(edge.dest);

        // uncomment the following code for undirected graph
        //adjList[edge.dest].push_back(edge.src);
    }
}