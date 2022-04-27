#include <vector>

// Data structure to store a graph edge
struct Edge {
    int src, dest;
};

class Graph
{
public:

    Graph(std::vector<Edge> const& edges, int n);

    std::vector<int>& operator[](std::size_t idx) {
        return m_adjList[idx];
    }

private:
    // a vector of vectors to represent an adjacency list
    std::vector<std::vector<int>> m_adjList;
};